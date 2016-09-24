#pragma once

//hooks class to make it easy for people to copy the style and expand on this small base
class cHooks
{
public:
	void Start();
	void Exit();
	cVMTHook* PanelVMT;
};

/*hooks just paint traverse atm ofc but here's some more if you understand what your doing and want to expand:
void __stdcall hkOverrideView(CViewSetup* vsView);
void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active);
void __stdcall hkFrameStageNotify(ClientFrameStage_t curStage);
void __fastcall hkDrawModelExecute(void* thisptr, void* edx, void* pRender, const void* &state, const ModelRenderInfo_t &pInfo, VMatrix *pCustomBoneToWorld);
*/
void __stdcall hkPaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce);