c*****************************************************
c**
c**     MODULE NAME AND RELEASE LEVEL
c**       ptranw.f , 25.1
c**    DATE AND TIME OF LAST MODIFICATION
c**       04/29/15 , 15:10:31
c**
c*****************************************************
C*
C* COPYRIGHT (C) 1987 MILLS DATA SYSTEMS CORPORATION
C*
C*******************************************************************
C
C                          PTRANW
C                          ------
C
C        THIS SUBROUTINE MANIPULATES THE RANFIL FOR ROUTINES THAT
C        NEED TEMPORARY STORAGE (GOTOPN, MOCNTL...).  AN INPUT
C        BUFFER IS PASSED IN AS AN ARGUEMENT WITH AN INDEX INTO
C        A LOGICAL BUFFER.  THIS ROUTINE CALCULATES WHICH RANFIL
C        RECORD IS NECESSARY TO ACCESS THE LOGICAL BUFFER.  IF THAT
C        RECORD IS ALREADY IN THE INPUT BUFFER, NOTHING HAPPENS.  
C        IF THAT RECORD IS NOT THE ONE IN THE INPUT BUFFER, THE CONTENTS
C        OF THE INPUT BUFFER IS WRITTEN INTO THE RANFIL AND THE 
C        CORRECT RECORD LOADED INTO THE INPUT BUFFER.  THE APPROPRIATE 
C        WORD IS THEN LOADED INTO THE OUTPUT BUFFER.
C
C*********************************************************************
C
      SUBROUTINE PTRANW(RBUFF,TWD,LIX,RIX)
      
      INCLUDE 'com8a.com'

      REAL*8 RBUFF(36),TWD
      INTEGER*2 LIX,RIX,TEMPIX

      TEMPIX= (LIX-1)/35
      IF (TEMPIX.NE.RIX) THEN
C            STORE THE CURRENT BUFFER AND GET THE CORRECT ONE
           CALL PUTRAN(RBUFF,IFL(4)+2+RIX)
           CALL GETRAN(RBUFF,IFL(4)+2+TEMPIX)
           RIX = TEMPIX
      ENDIF
      RBUFF(LIX-RIX*35) = TWD
99999 RETURN
      END
