/*
 * Copyright 2007-2010 (C) - Frictional Games
 *
 * This file is part of OALWrapper
 *
 * For conditions of distribution and use, see copyright notice in LICENSE
 */
/**
	@file OAL_Loaders.h
	@author Luis Rodero
	@date 2006-10-02
	@version 0.1
	Set of functions to load and unload samples and streams in OpenAL
*/

#ifndef _OAL_LOADERS_H
#define _OAL_LOADERS_H

#include "OAL_Types.h"

cOAL_Sample*	OAL_Sample_Load		( const string &asFilename );
cOAL_Sample*	OAL_Sample_Load		( const wstring &asFilename );
void			OAL_Sample_Unload	( cOAL_Sample* apSample );


cOAL_Stream*	OAL_Stream_Load		( const string &asFilename );
cOAL_Stream*	OAL_Stream_Load		( const wstring &asFilename );
void			OAL_Stream_Unload	( cOAL_Stream* apStream );

void OAL_Sample_SetLoop ( cOAL_Sample* apSample, bool abLoop );
void OAL_Stream_SetLoop ( cOAL_Stream* apStream, bool abLoop );

int OAL_Sample_GetChannels (cOAL_Sample* apSample);
int OAL_Stream_GetChannels (cOAL_Stream* apStream);


#endif	// _OAL_PLAYBACK_H
