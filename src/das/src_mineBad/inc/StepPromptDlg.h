/************************************************************************
c
c   FILE NAME: StepPromptDlg.h
c
c	 CONTAINS: 
c		Header file for the class CStepPromptDlg 
c
c     COPYRIGHT 2013 (c) Numerical Control Computer Sciences.
c           All Rights Reserved
c      MODULE NAME AND RELEASE LEVEL
c       StepPromptDlg.h , 25.1
c    DATE AND TIME OF LAST  MODIFICATION
c       04/29/15 , 15:06:07
c
c**********************************************************************
*/
#if !defined(AFX_STEPPROMPTDLG_H__51B54AD4_C8FB_11D3_8112_00C04F336F5E__INCLUDED_)
#define AFX_STEPPROMPTDLG_H__51B54AD4_C8FB_11D3_8112_00C04F336F5E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StepPromptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStepPromptDlg dialog

class CStepPromptDlg : public CDialog
{

protected:

	int m_cols, m_lns;
	CString m_msg, m_input, m_title;

// Construction
public:
	CStepPromptDlg(CWnd* pParent = NULL); 
	void SetDlgValue(int cols = 80, int lns=1, char *title = NULL, char *msg=NULL, char*input=NULL);
	void GetInput(char *input, int maxnum = 80);
// Dialog Data
	//{{AFX_DATA(CStepPromptDlg)
	enum { IDD = IDD_PROMPT };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStepPromptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStepPromptDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEPPROMPTDLG_H__51B54AD4_C8FB_11D3_8112_00C04F336F5E__INCLUDED_)
