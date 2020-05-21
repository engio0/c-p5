@echo off
rem   This file will clean out any temporary Pro/E files which are
rem   not required.  Simply type "clean" in the desired directory 
rem   to clean it out. Or access it from the UTILITIES menu under
rem   MISC.
del *.inf* /S /F
del *.ger* /S /F
del *.crc* /S /F
del *.memb* /S /F
del *.ers* /S /F
del iges_stats.dat* /S /F
del *.bde /S /F
del *.bdi /S /F
del *.bdm /S /F
del *.m_p* /S /F
del *.bom* /S /F
del *.ptd /S /F
del *.als /S /F
del *.dat /S /F
del *.pls /S /F
del s2d0*.sec* /S /F
del *.idx /S /F
del *.xml /S /F
del *.win /S /F
del *.tst /S /F
del *.pic /S /F
del *.log* /S /F
del *.out /S /F
del *.trl /S /F
del *.bak /S /F
rem del *.stp /S /F
rem del *.iges /S /F
rem del *.igs /S /F
del *.csv.* /S /F
rem del *.pro /S /F
del *.txt.* /S /F
del *.crc /S /F
del *.win.* /S /F
del *.err.* /S /F
del *.sec.* /S /F
del *.ptb /S /F
del *.err_* /S /F
del *.err.* /S /F
del *.log /S /F
del *.xml.* /S /F
rem
rem
rem Working Directory Purge
rem
rem call d:\ptc\ProeWildfire50\bin\purge.bat
rem
rem Trail Directory Purge
rem d:
rem cd \prodata\trail_dir\
rem call d:\ptc\ProeWildfire50\bin\purge.bat
PUSHD D:\prodata\trail_dir
CALL purge1
POPD
