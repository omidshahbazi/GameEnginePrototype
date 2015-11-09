// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Movie.h>
#include <Public\Core.h>
#include <Public\Renderer\TextureResourcesManager.h>
#include <Public\CTime.h>


BEGIN_NAMESPACE
	
static GUID MY_CLSID_AMMultiMediaStream={0x49C47CE5,0x9BA4,0x11D0,0x82,0x12,0x00,0xC0,0x4F,0xC3,0x2C,0x45};
static GUID MY_IID_IAMMultiMediaStream={0xBEBE595C,0x9A6F,0x11D0,0x8F,0xDE,0x00,0xC0,0x4F,0xD9,0x18,0x9D};
static GUID MY_MSPID_PrimaryVideo={0xA35FF56A,0x9FDA,0x11D0,0x8F,0xDF,0x00,0xC0,0x4F,0xD9,0x18,0x9D};
static GUID MY_IID_IDirectDrawMediaStream={0xF4104FCE,0x9A70,0x11D0,0x8F,0xDE,0x00,0xC0,0x4F,0xD9,0x18,0x9D}; 
static GUID MY_MSPID_PrimaryAudio={0xA35FF56B,0x9FDA,0x11D0,0x8F,0xDF,0x00,0xC0,0x4F,0xD9,0x18,0x9D};

Movie::Movie(const String &RelativeFilePath) :
	m_FPS(0),
	m_Loop(false),
	m_StartTime(0)
{
	CoInitialize(NULL);

	CoCreateInstance(MY_CLSID_AMMultiMediaStream, 0, 1, MY_IID_IAMMultiMediaStream, (void**)&m_MediaStream);

	m_MediaStream->Initialize(STREAMTYPE_READ, 0, NULL);
	m_MediaStream->AddMediaStream(0, &MY_MSPID_PrimaryVideo, 0, NULL);
	m_MediaStream->AddMediaStream(0, &MY_MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL);

	wchar_t path[512];
	//MultiByteToWideChar(CP_ACP, 0, (Core::GetReference().GetMoviePath() + RelativeFilePath).GetBuffer(), -1, path, 512);
	m_MediaStream->OpenFile(path, AMMSF_RENDERTOEXISTING);

	m_MediaStream->GetMediaStream(MY_MSPID_PrimaryVideo, &m_VideoStream);
	m_VideoStream->QueryInterface(MY_IID_IDirectDrawMediaStream, (void**)&m_DrawStream);
	m_DrawStream->CreateSample(0, 0, 0, &m_Sample);

	STREAM_TIME time;
	m_MediaStream->GetDuration(&time);
	m_Duration = time / 10000.f;

	RECT rect;
	m_Sample->GetSurface(&m_Surface, &rect);
	m_Size.X = float32(rect.right - rect.left);
	m_Size.Y = float32(rect.bottom - rect.top);


	m_Engine = Core::GetReference().GetRenderer();

	//m_Texture = (Texture*)TextureResourcesManager::GetReference().CreateTexture(RelativeFilePath + "_Texture", m_Size);
}


Movie::~Movie(void)
{
    m_VideoStream->Release();
    m_DrawStream->Release();

    m_Sample->Release();
    m_Surface->Release();

    m_MediaStream->Release();

    CoUninitialize();

	LOG_INFO_DEBUG("IMovie destoryed successfully")
}


void Movie::Update(void)
{
	//
	// Update frame if it's nessessary
	//
	if (GetTickCount() - m_LastUpdateTime < m_FPS)
		return;

	m_LastUpdateTime = GetTickCount();
	m_Sample->Update(0, NULL, NULL, 0);

	//
	// Copy current frame on Texture
	//
	//void *bits = m_Texture->GetIrrLichtTexture()->lock();
	//uint32 pitch = m_Texture->GetIrrLichtTexture()->getPitch(); 

	//DDSURFACEDESC surface;
	//surface.dwSize = sizeof(DDSURFACEDESC);
	//m_Surface->Lock(NULL, &surface, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT , NULL);

	//int32 minSize = (pitch < surface.lPitch) ? pitch : surface.lPitch;

	//for(uint32 h = 0; h < surface.dwHeight; h++)
	//	memcpy((BYTE*)bits + ((0 + h) * pitch) + 0 * 4, (BYTE*)surface.lpSurface + h * surface.lPitch, minSize);

	//m_Surface->Unlock( NULL);
	//m_Texture->GetIrrLichtTexture()->unlock();

	const float32 currTime = Time::GetReference().GetRealTime();

	if (m_Loop && currTime - m_StartTime >= m_Duration)
	{
		Stop();

		Play();
	}
}


void Movie::Play(void)
{
	m_MediaStream->SetState(STREAMSTATE_RUN);

	m_StartTime = Time::GetReference().GetRealTime();
}


void Movie::Pause(void)
{
	m_MediaStream->SetState(STREAMSTATE_STOP);
}


void Movie::Stop(void)
{
	m_MediaStream->SetState(STREAMSTATE_STOP);
	m_MediaStream->Seek(0);
}

END_NAMESPACE
