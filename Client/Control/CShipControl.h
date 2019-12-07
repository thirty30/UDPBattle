#pragma once

class CActor;
class CShipControl : public CSingleton<CShipControl>
{
public:
	CActor* pActor;

public:
	CShipControl();
	~CShipControl();

	void ControlKeyPress(n32 a_nKey, n32 a_nScancode, n32 a_nAction, n32 a_nMods);
	void ControlMousePress(n32 a_nKey, n32 a_nAction, n32 a_nMods);
	void ControlCursor(f64 a_fX, f64 a_fY);

};
