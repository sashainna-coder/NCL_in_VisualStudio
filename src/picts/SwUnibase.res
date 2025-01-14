        ��  ��                  �      �� ��     0 	        �4   V S _ V E R S I O N _ I N F O     ���               ?                        D   S t r i n g F i l e I n f o       0 4 0 9 0 4 B 0        C o m p a n y N a m e     J   F i l e D e s c r i p t i o n     S w U n i b a s e   M o d u l e     6   F i l e V e r s i o n     1 ,   0 ,   0 ,   1     4 
  I n t e r n a l N a m e   S w U n i b a s e   B   L e g a l C o p y r i g h t   C o p y r i g h t   2 0 0 3     D   O r i g i n a l F i l e n a m e   S w U n i b a s e . D L L   B   P r o d u c t N a m e     S w U n i b a s e   M o d u l e     :   P r o d u c t V e r s i o n   1 ,   0 ,   0 ,   1     (    O L E S e l f R e g i s t e r     D    V a r F i l e I n f o     $    T r a n s l a t i o n     	�U  0   R E G I S T R Y   ��f       0	        /*********************************************************************
**  NAME:  SwUnibaseObj.rgs
**
** CONTAINS:
**
**       NCL/Solid class registration routines for SolidWorks.
**
**    COPYRIGHT 2003 (c) NCCS.  All Rights Reserved.
**    MODULE NAME AND RELEASE LEVEL
**       %M% , %I%
**    DATE AND TIME OF LAST  MODIFICATION
**       %G% , %U%
*********************************************************************/
HKCR
{
	SwUnibase.SwUnibaseObj.1 = s 'SwUnibaseObj Class'
	{
		CLSID = s '{46A48BB9-9093-11D7-87E7-0800691362A7}'
	}
	SwUnibase.SwUnibaseObj = s 'SwUnibaseObj Class'
	{
		CLSID = s '{46A48BB9-9093-11D7-87E7-0800691362A7}'
		CurVer = s 'SwUnibase.SwUnibaseObj.1'
	}
	NoRemove CLSID
	{
		ForceRemove {46A48BB9-9093-11D7-87E7-0800691362A7} = s 'SwUnibaseObj Class'
		{
			ProgID = s 'SwUnibase.SwUnibaseObj.1'
			VersionIndependentProgID = s 'SwUnibase.SwUnibaseObj'
			ForceRemove 'Programmable'
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Apartment'
			}
			'TypeLib' = s '{46A48BA1-9093-11D7-87E7-0800691362A7}'
		}
	}
}
HKLM
{
	NoRemove SOFTWARE
	{
		NoRemove SolidWorks
		{
			NoRemove AddIns
			{
				ForceRemove {46A48BB9-9093-11D7-87E7-0800691362A7} = d '0'
				{
					val Description = s 'SwUnibase AddIn'
					val Title = s 'SwUnibase'
				}
			}
		}
	}
}
   �  0   R E G I S T R Y   ��k       0	        /*********************************************************************
**  NAME:  SwPMPage.rgs
**
** CONTAINS:
**
**       NCL/Solid class registration routines for SolidWorks.
**
**    COPYRIGHT 2003 (c) NCCS.  All Rights Reserved.
**    MODULE NAME AND RELEASE LEVEL
**       %M% , %I%
**    DATE AND TIME OF LAST  MODIFICATION
**       %G% , %U%
*********************************************************************/
HKCR
{
	SwUnibase.PMPage.1 = s 'PMPage Class'
	{
		CLSID = s '{46A48BB7-9093-11D7-87E7-0800691362A7}'
	}
	SwUnibase.PMPage = s 'PMPage Class'
	{
		CLSID = s '{46A48BB7-9093-11D7-87E7-0800691362A7}'
	}
	NoRemove CLSID
	{
		ForceRemove {46A48BB7-9093-11D7-87E7-0800691362A7} = s 'PMPage Class'
		{
			ProgID = s SwUnibase.PMPage.1
			VersionIndependentProgID = s SwUnibase.PMPage
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Apartment'
			}
		}
	}
}
   �  0   R E G I S T R Y   ��l       0	        /*********************************************************************
**  NAME:  SwPart.rgs
**
** CONTAINS:
**
**       NCL/Solid class registration routines for SolidWorks.
**
**    COPYRIGHT 2003 (c) NCCS.  All Rights Reserved.
**    MODULE NAME AND RELEASE LEVEL
**       %M% , %I%
**    DATE AND TIME OF LAST  MODIFICATION
**       %G% , %U%
*********************************************************************/
HKCR
{
	SwUnibase.Part.1 = s 'Part Class'
	{
		CLSID = s '{46A48BAF-9093-11D7-87E7-0800691362A7}'
	}
	SwUnibase.Part = s 'Part Class'
	{
		CLSID = s '{46A48BAF-9093-11D7-87E7-0800691362A7}'
	}
	NoRemove CLSID
	{
		ForceRemove {46A48BAF-9093-11D7-87E7-0800691362A7} = s 'SwUnibaseObj Class'
		{
			ProgID = s SwUnibase.Part.1
			VersionIndependentProgID = s SwUnibase.Part
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Apartment'
			}
		}
	}
}
   �  0   R E G I S T R Y   ��m       0	        /*********************************************************************
**  NAME:  SwAssembly.rgs
**
** CONTAINS:
**
**       NCL/Solid class registration routines for SolidWorks.
**
**    COPYRIGHT 2003 (c) NCCS.  All Rights Reserved.
**    MODULE NAME AND RELEASE LEVEL
**       %M% , %I%
**    DATE AND TIME OF LAST  MODIFICATION
**       %G% , %U%
*********************************************************************/
HKCR
{
	SwUnibase.Assembly.1 = s 'Assembly Class'
	{
		CLSID = s '{46A48BB1-9093-11D7-87E7-0800691362A7}'
	}
	SwUnibase.Assembly = s 'Assembly Class'
	{
		CLSID = s '{46A48BB1-9093-11D7-87E7-0800691362A7}'
	}
	NoRemove CLSID
	{
		ForceRemove {46A48BB1-9093-11D7-87E7-0800691362A7} = s 'Assembly Class'
		{
			ProgID = s SwUnibase.Assembly.1
			VersionIndependentProgID = s SwUnibase.Assembly
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Apartment'
			}
		}
	}
}
   �  0   R E G I S T R Y   ��n       0	        /*********************************************************************
**  NAME:  SwDrawing.rgs
**
** CONTAINS:
**
**       NCL/Solid class registration routines for SolidWorks.
**
**    COPYRIGHT 2003 (c) NCCS.  All Rights Reserved.
**    MODULE NAME AND RELEASE LEVEL
**       %M% , %I%
**    DATE AND TIME OF LAST  MODIFICATION
**       %G% , %U%
*********************************************************************/
HKCR
{
	SwUnibase.Part.1 = s 'Drawing Class'
	{
		CLSID = s '{46A48BB3-9093-11D7-87E7-0800691362A7}'
	}
	SwUnibase.Part = s 'Drawing Class'
	{
		CLSID = s '{46A48BB3-9093-11D7-87E7-0800691362A7}'
	}
	NoRemove CLSID
	{
		ForceRemove {46A48BB3-9093-11D7-87E7-0800691362A7} = s 'Drawing Class'
		{
			ProgID = s SwUnibase.Part.1
			VersionIndependentProgID = s SwUnibase.Part
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Apartment'
			}
		}
	}
}
   �  0   R E G I S T R Y   ��o       0	        /*********************************************************************
**  NAME:  SwDocView.rgs
**
** CONTAINS:
**
**       NCL/Solid class registration routines for SolidWorks.
**
**    COPYRIGHT 2003 (c) NCCS.  All Rights Reserved.
**    MODULE NAME AND RELEASE LEVEL
**       %M% , %I%
**    DATE AND TIME OF LAST  MODIFICATION
**       %G% , %U%
*********************************************************************/
HKCR
{
	SwUnibase.DocView.1 = s 'DocView Class'
	{
		CLSID = s '{46A48BB5-9093-11D7-87E7-0800691362A7}'
	}
	SwUnibase.DocView = s 'DocView Class'
	{
		CLSID = s '{46A48BB5-9093-11D7-87E7-0800691362A7}'
	}
	NoRemove CLSID
	{
		ForceRemove {46A48BB5-9093-11D7-87E7-0800691362A7} = s 'DocView Class'
		{
			ProgID = s SwUnibase.DocView.1
			VersionIndependentProgID = s SwUnibase.DocView
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Apartment'
			}
		}
	}
}
   �      �� ��y     0	        (   B                                    �  �   �� �   � � ��  ��� ���   �  �   �� �   � � ��  ��� �wwwwwwwwz���������wwwwww������ww   �wwwwwwwwz�����������www��������w   �wwwwwwwwz���wwwwww��wwy��������w   ��wwwwwww����wwwwww|��wy��wwww��w   ��wwwwwww�w��wwwwwww��w��wwwwwy�w   z�wwwwwwz�w��wwwwwww��y��wwwwww�w   z�wwwwwwz�w��wwwwwww�wy�wwwwwwwww   z��wwwww��w��wwwwww|�w��wwwwwwwww   w��������ww��wwwwww|�w��wwwwwwwww   wz�������ww��wwwww��ww��wwwwwwwww   ww�������ww���������ww��wwwwwwwww   ww��www��ww���������ww��wwwwwwwww   wwz�www�www����������w��wwwwwwwww   wwz�wwz�www��wwwwww|�Ǚ�wwwwwwwww   www��wz�www��wwwwwww�Ǚ�wwwwwwwww   www��w��www��wwwwwww�Ǚ�wwwwwww�w   wwwz�w�wwww��wwwwwww��y��wwwwwy�w   wwwz�z�wwww��wwwwwww��w��wwwww��w   wwww���wwww��wwwwww|��wy���wwy��w   wwww���wwww��wwwwww|�www��������w   wwwwz�wwwww����������wwwy�������w   wwwwz�wwwww���������wwwww����wwww   �      �� ��z     0	        (   0            h                        �  �   �� �   � � ��  ��� ���   �  �   �� �   � � ��  ��� wwwwwwwwwwwwwwwwwwwwwwwwy���ə��y�����̗y�����ɗy���ə��y�����̗y�����ɗy���ə��y���̙��y�ə��ɗy���ə��y����ə�y�����ɗy���ə��y����̙�y�����ɗy���ə��y����̙�y�����ɗy���ə��y����̙�y�����ɗy���ə��|̙��̙�y�����ɗy���ə��|̙��̙�y�����ɗy���ə��y�ə�̙�y�����ɗy���ə��y����̙�y�ə��ɗy���ə��y����ə�y�����ɗy���ə��y���ə��y����̙�wwwwwwwwwwwwwwwwwwwwwwww$      �� ��{     0	         ��        � Ȁ     � �     C r e a t e   N C L   U n i b a s e       M S   S a n s   S e r i f              P1 � 2     ��� O K               P� � 2     ��� C a n c e l               P  B  �  ��� E n t i t y   L a b e l   O p t i o n s :               !PK  Z 1 �  ���               P < � 7 ������� N a m e   M o d a l s                 P K   �  ��� S u r f a c e s :               � �P� K 7  �  ���             !P2 K A 1 �  ���               P _   �  ��� C u r v e s :               !P2 _ A 1 �  ���             � �P� _ 7  �  ���               P x � E ������� L a b e l   M a t c h i n g               P
 � A 
 �  ��� U n i b a s e   f o r   L a b e l s :              � �PK � _  �  ���               P� � -  �  ��� B r o w s e . . .               � �P7 � )  �  ���               P � & 
 �  ��� T o l e r a n c e :               P 
  
 �  ��� U n i b a s e :            � �P(  }  �  ���               P�  -  �  ��� B r o w s e . . .                P - _ 
 �  ��� E x p o r t   B o u n d a r y   C u r v e s              Px - i 
 �  ��� E x p o r t   S u r f a c e s   a s   S h a d e d                 P � 3 
 �   ��� M a t c h i n g   L e v e l :               !PH � > < �   ���               P� � 4  �   ��� A t t r i b u t e s           �� ��|     0	        �Ȁ         � �     C r e a t i n g   N C L   U n i b a s e    M S   S a n s   S e r i f      P    % � 2   ��� O K         P    � � 2   ��� C a n c e l        �P     z �  � m s c t l s _ p r o g r e s s 3 2   P r o g r e s s 1     �P    	  � b � ���       �      �� ��}     0	        � Ȁ          � �     L a b e l   M a t c h i n g   A t t r i b u t e s    M S   S a n s   S e r i f    P    ! � 2   ��� O K         P    o � 2   ��� C a n c e l         P     K �  ����� L e v e l   2     � �P    )  ,  � ���         P    
   
 ����� L a y e r :       !P    y  ; 1 � ���         P    ]    ����� C o l o r :         P     � �  ����� L e v e l   4       P      �  ����� E x a c t   M a t c h       P     n �  ����� L e v e l   3       P     ( �  ����� L e v e l   1       P    
 4  
 ����� L a y e r :         P    
 y  
 ����� L a y e r :         P    
 V  
 ����� L a y e r :         P     �  
 ����� L a y e r :       � �P    ) 2 ,  � ���       � �P    ) T ,  � ���       � �P    ) w ,  � ���       � �P    * � ,  � ���         P    ] 4   ����� C o l o r :         P    ] W   ����� C o l o r :         P    ] x   ����� C o l o r :         P    ] �   ����� C o l o r :       !P    y 1 ; 1 � ���       !P    y T ; 1 � ���       !P    y v ; 1 � ���       !P    x � ; 1 � ���         P     � �  ����� U n m a t c h e d       P     �  
 ����� L a y e r :       � �P    * � ,  � ���         P    ] �   ����� C o l o r :       !P    x � ; 1 � ���       �       ��� ��{     0 	        �	   Generate �   Using Existing Unibase �   Prefix �
   Subscript �   Prefix �
   Subscript �    Exact Match �    Level 1 �    Level 2 �    Level 3 �    Level 4   `      ��� ��}     0 	        �    Default �    White �    Blue �    Red �    Green �    Magenta �    Yellow �    Cyan �    Brown �    Tan �    Lt Blue � 
   Sea Green �    Orange �    Pink �    Purple �    Grey �    Default �    White �    Blue �    Red �    Green �    Magenta �    Yellow �    Cyan �    Brown �    Tan �    Lt Blue � 
   Sea Green �    Orange �    Pink �    Purple �    Grey �    Default �    White �    Blue �    Red �    Green �    Magenta �    Yellow �    Cyan �    Brown �    Tan �    Lt Blue � 
   Sea Green �    Orange �    Pink �    Purple �    Grey �    Default �    White �    Blue �    Red �    Green �    Magenta �    Yellow �    Cyan �    Brown �    Tan �    Lt Blue � 
   Sea Green �    Orange �    Pink �    Purple �    Grey �    Default �    White �    Blue �    Red �    Green �    Magenta �    Yellow �    Cyan �    Brown �    Tan �    Lt Blue � 
   Sea Green �    Orange �    Pink �    Purple �    Grey �    Default �    White �    Blue �    Red �    Green �    Magenta �    Yellow �    Cyan �    Brown �    Tan �    Lt Blue � 
   Sea Green �    Orange �    Pink �    Purple �    Grey   8  ,   T Y P E L I B   ��     0 	        MSFT      	      A                            �       ����       �             d   �   ,  �  �  X  �     �  �  L  t  �  ����   �     ����   �     ����   <  `   ����   $  �   ����   �  �  ����   �     ����   �
  x  ����   <  8  ����   t     ����   ����    ����   |     ����   �     ����   ����    ����   ����    ����   %"  �      ����                           H                        ����                  ����4" �     �                             �   @  0       0           ���� (             ����%" 8      ����                           �      �       �           ����                 ����4" 8      ����                           �   @  �       �           ����              ����%" 8      ����                           �      �       �           ����                  ����4" 8      ����                           �   @  �       �           ����              ����%" 8      ����                                �       �           ����      0           ����4" 8      ����                              @        �           ����              ����%" 8      ����                           8     (      �           ����      @           ����4"	 8      ����                           P  @  <                 ����              ����%"
 8      ����                           h     P                ����      P           ����4" 8      ����                           �  @  d      $          ����              ������������x   ��������    �����������������   �   ����������������8  �  h  �   �        P  0   �������������   H   ����   ���F����� ib���������c�w�|Q���  �w<���������d�w�|Q���  �w<������������F����� ib�    ����0     �      F   ����      �      F   �������F����� ib�d   �������F����� ib��   �������F����� ib�,  �������F����� ib��  �������F����� ib��  �������F����� ib�X  �������F����� ib��  �������F����� ib�   �������F����� ib��  �������F����� ib��  `   ���F����� ib�L  ����d      ��������,     ���������     ���������     ���������     ��������L     ��������      x   `          - stdole2.tlbWWW����������������    �����   ���������������������������������������������   ����   ���������������������������������������������   �����������������   ������������������������������������  ����������������d  ��������P  ����������������(  ������������������������������������������������h   ��������������������������������������������L   ���������������������������������������������������������������������������������   ������������0   ���������������������   ��������������������<  �����������������   �������� �SWUNIBASELib    ����8�SwUnibaseObjd   ����8n�ISwUnibaseObjWWWd   ���� �CreateUnibaseWWWd   ���� �&ToolbarUpdateWWW�������� �+statusWWd   ����
 %~DisplayPMPWW�   ����8�PMPageWW,  ����8CIPMPageW�  ����8�~Part�  ����8�<IPartWWWX  ����8jAssembly�  ����	8/�IAssemblyWWW   ����8<0DrawingW�  ����8zIDrawing�  ����8�DocViewWL  ����84�IDocView SwUnibase 1.0 Type Library SwUnibaseObj Class ISwUnibaseObj InterfaceWWW Create Unibase Toolbar Update Display PropertyManagerPageWWW PMPage ClassWW IPropertyManagerPage Interface
 Part Class IDocument InterfaceWWW Assembly Class Drawing ClassW IDrawing Interface DocView ClassW IDocView Interface @ � �,�@WW � WW       ����0          l        �     4 	          L   ,   �      L 	D        \       �   
       �    $ 4 	         l            L   h   �           L   �       �� ��     0	                	 S w U n i b a s e      P M P a g e   C l a s s 
 P M P a g e @ N C L 
 D i s p l a y P M P  D i s p l a y   T h e   P r o p e r t y M a n a g e r P a g e                 �� ��     0	         N C L  C r e a t e   U n i b a s e @ N C L  C r e a t e U n i b a s e  C r e a t e U n i b a s e  S a m p l e   t o o l b a r   t i t l e  C r e a t e U n i b a s e  T o o l b a r U p d a t e  T o o l b a r   h i n t   t e x t  T o o l b a r   t i p   t e x t               