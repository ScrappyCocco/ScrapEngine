#define DR_WAV_IMPLEMENTATION
#include <Engine/Audio/Buffer/Wav/WavAudioBuffer.h>

void ScrapEngine::Audio::WavAudioBuffer::load_file(const std::string& filename)
{
	p_wav_ = drwav_open_file(filename.c_str());
	if (p_wav_ == nullptr)
	{
		throw std::runtime_error("[WavAudioBuffer]Error opening wav file: " + filename);
	}

	//Set the format
	const ALenum format = to_al_format(p_wav_->channels, p_wav_->bitsPerSample);
	if(format == -1)
	{
		throw std::runtime_error("[WavAudioBuffer]Audio format error, only 16bit audio are supported...");
	}
	is_stereo_ = is_stereo(p_wav_->channels);

	//Set the sample rate
	const ALsizei freq = static_cast<ALsizei>(p_wav_->sampleRate);

	//Allocate and read content of file
	const size_t memory_size = static_cast<size_t>(p_wav_->totalPCMFrameCount) * p_wav_->channels * sizeof(int16_t);
	int16_t* p_sample_data = static_cast<int16_t*>(malloc(memory_size));
	drwav_read_pcm_frames_s16(p_wav_, p_wav_->totalPCMFrameCount, p_sample_data);

	//Convert size
	const ALsizei buffer_size = static_cast<ALsizei>(memory_size);

	//Fill buffer
	alBufferData(buffer_, format, p_sample_data, buffer_size, freq);

	//Free memory
	drwav_close(p_wav_);
}
