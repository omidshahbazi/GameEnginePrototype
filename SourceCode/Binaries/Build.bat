::Copyright 2012-2015 ?????????????. All Rights Reserved.

IF EXIST ..\..\Binaries\Frontend.exe (
	..\..\Binaries\Frontend.exe %*
	popd
	EXIT /B %ERRORLEVEL%
) ELSE (
	ECHO Frontend.exe not found in Binaries folder
	popd
	EXIT /B 404
)