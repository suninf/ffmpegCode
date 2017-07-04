#pragma once

#include "EvHeade.h"

class Encode
{
public:
	Encode();
	int Open(const char * file);
	void Close();

	int NewVideoStream(int width, int height);
	int NewAudioStream();

	int WriteHeader();
	int WriteVideo(AVPacket *packet);
	int WriteAudio(AVPacket *packet);
	int WriteTrailer();
protected:
	AVFormatContext* formatCtx_ = NULL;
	AVOutputFormat* output_ = NULL;

	AVStream* videoStream_ = NULL;
	AVCodecContext* videoCodecCtx_ = NULL;
	AVCodec* videoCodec_ = NULL;

	AVStream* audioStream_ = NULL;
	AVCodecContext* audioCodecCtx_ = NULL;
	AVCodec* audioCodec_ = NULL;
};

class OriginalEncode
	:public Encode
{
public:
	int EncodeAudio(AVFrame* frame);
	int EncodeVideo(AVFrame* frame);
	int FlushAudio();
	int FlushVideo();

	AVStream* GetVideoStream();
	AVStream* GetAudioStream();
private:
	AVPacket videoPacket_;
	AVPacket audioPacket_;
};