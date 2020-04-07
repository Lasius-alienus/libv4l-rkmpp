/*
 *  Copyright (c) 2019, Fuzhou Rockchip Electronics Co., Ltd
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#ifndef LIBV4L_RKMPP_ENC_H
#define LIBV4L_RKMPP_ENC_H

#include "libv4l-rkmpp.h"

#ifndef V4L2_CID_MPEG_VIDEO_H264_SPS_PPS_BEFORE_IDR
#define V4L2_CID_MPEG_VIDEO_H264_SPS_PPS_BEFORE_IDR	(V4L2_CID_MPEG_BASE+388)
#endif

/**
 * struct rkmpp_enc_context - Context private data for encoder
 * @ctx:		Common context data.
 * @mpp_streaming:	The mpp is streaming.
 * @h264:		Enc config for H264.
 * @mb_rc:		V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE.
 * @rc_reaction_coeff:	V4L2_CID_MPEG_MFC51_VIDEO_RC_REACTION_COEFF.
 * @gop_size:		V4L2_CID_MPEG_VIDEO_GOP_SIZE.
 * @fixed_bitrate:	V4L2_CID_MPEG_MFC51_VIDEO_RC_FIXED_TARGET_BIT.
 * @bitrate:		Target bitrate.
 * @framerate:		Target framerate.
 * @encoder_thread:	Handler of the encoder thread.
 * @encoder_cond:	Condition variable for streaming flag.
 * @encoder_mutex:	Mutex for streaming flag and buffers.
 */
struct rkmpp_enc_context {
	struct rkmpp_context *ctx;
	struct v4l2_rect crop;

	bool mpp_streaming;

	struct {
		int profile;
		int level;
		int max_qp;
		bool separate_header; /* V4L2_CID_MPEG_VIDEO_HEADER_MODE */
		bool needs_header;
		MppPacket header;
	} h264;

	bool mb_rc;
	int rc_reaction_coeff;
	int gop_size;
	bool fixed_bitrate;

	int bitrate;
	int framerate;

	int width;
	int height;
	int hstride;
	int vstride;

	pthread_t encoder_thread;
	pthread_cond_t encoder_cond;
	pthread_mutex_t encoder_mutex;
};

bool rkmpp_enc_has_event(void *data);
void *rkmpp_enc_init(struct rkmpp_context *ctx);
int rkmpp_enc_ioctl(void *data, unsigned long cmd, void *arg);
void rkmpp_enc_deinit(void *data);

#endif //LIBV4L_RKMPP_ENC_H
