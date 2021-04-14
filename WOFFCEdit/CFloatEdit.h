#pragma once
#include <afxwin.h>
class CFloatEdit :
    public CEdit
{
protected:
	void UpdateContents();

public:
	
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	DECLARE_MESSAGE_MAP()
};
