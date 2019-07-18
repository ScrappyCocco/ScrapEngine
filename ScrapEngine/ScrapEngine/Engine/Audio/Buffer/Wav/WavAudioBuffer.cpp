#define DR_WAV_IMPLEMENTATION
#include <Engine/Audio/Buffer/Wav/WavAudioBuffer.h>
#include <dr_wav.h>

void ScrapEngine::Audio::WavAudioBuffer::load_file(const std::string& filename)
{
	drwav* p_wav = drwav_open_file(filename.c_str());

	if (p_wav == nullptr)
	{
		throw std::runtime_error("[WavAudioBuffer]Error opening wav file: " + filename);
	}

	//Set the format
	const ALenum format = to_al_format(p_wav->channels, p_wav->bitsPerSample);
	if(format == -1)
	{
		throw std::runtime_error("[WavAudioBuffer]Audio format error, only 16bit audio are supported...");
	}
	is_stereo_ = is_stereo(p_wav->channels);

	//Set the sample rate
	const ALsizei freq = static_cast<ALsizei>(p_wav->sampleRate);

	//Allocate and read content of file
	const size_t memory_size = static_cast<size_t>(p_wav->totalPCMFrameCount) * p_wav->channels * sizeof(int16_t);
	std::unique_ptr<int16_t> p_sample_data(new int16_t[memory_size]);
	drwav_read_pcm_frames_s16(p_wav, p_wav->totalPCMFrameCount, p_sample_data.get());

	//Convert size
	const ALsizei buffer_size = static_cast<ALsizei>(memory_size);

	//Fill buffer
	alBufferData(buffer_, format, p_sample_data.get(), buffer_size, freq);

	//Free memory
	drwav_close(p_wav);
	p_sample_data.reset();
}
