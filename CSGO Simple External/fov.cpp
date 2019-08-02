#include "includes.h"

cFov *pFov = new cFov;

cFov::cFov()
{

}

cFov::~cFov()
{

}

void cFov::setViewFov()
{
	while (pLocalPlayer->getFOV() != fov)
	{
			Mem->Write<int>(pLocalPlayer->getLocalPLayer() + m_iFOV, fov);
	}
}
