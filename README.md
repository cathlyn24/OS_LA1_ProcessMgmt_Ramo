Build Instructions for VS Code (MinGW)

I. Installing MinGW-w64
    1. Go to https://winlibs.com/
    2. Download the latest "MinGW-w64 + GCC" for Windows:
	Choose UCRT runtime (recommended for modern systems) 
	Pick posix threads build (for instance GCC 15.2.0 (with POSIX threads) + MinGW-w64 13.0.0 (UCRT) - release 1  (LATEST)) and download the Zip Archive in Win64 (for Windows 64-bit) 
    3. Extract the .zip file to a folder.
II. Add MinGW-w64 to PATH
1.	Press Win + R, type sysdm.cpl, and press Enter.
2.	Go to Advanced > Environment Variables.
3.	Under System variables, find Path and click Edit.
4.	Click New and add the bin path of MinGW, e.g.: C:\Users\Administrator\OneDrive\Desktop\mingw64\bin
5.	Click OK on all dialogs to save.
6.	Verify the installation in Windows Powershell or CMD by running gcc –version
 III. Creating a folder
1.	 Create a new folder and named it OS_ProcessMgmt_Lastname
2.	Inside the OS_ProcessMgmt_Lastname, create a src folder for your .c files
IV. Creating a single child C program in Visual Studio Code
1.	Open VS Code and install C/C++ extensions by Microsoft
2.	In the file menu, select Open Folder and choose the src folder that you created earlier.
3.	Inside the src folder, create a new file and named it child_echo.c
4.	Write a program for child_echo.c that prints its own PID and the parent PID passed as an argument.
5.	Create another file and named it create_basic.c
6.	Write a program that prints the parent PID, calls CreateProcess() to launch child_echo.exe., then wait for the child finish, and prints the child’s exit code.
7.	Compile both files
8.	In the Powershell, run gcc create_basic.c  -o create_basic.exe, then after that run the command .\create_basic.exe, and record the output.

V. Creating two children
1. Still in the VS code, create a new file in the src folder and name it create_two_children.c, then write a program that spawns two child processes in parallel. You can use the “child_echo.exe” for this activity. It should use WaitForMultipleObjects() or two separate waits, and each child should report its own PID.
2. In the Powershell, run gcc create_two_children.c  -o create_two_children.exe, then after that run the command .\create_two_children.exe, then record the output.
VI. Simulating exec()
1.	Again, create a new file and named it replace_sim.c and write a program that the parent should create a new process (for example, cmd /c dir) and exit with the same code as the spawned program.
2.	. In the Powershell, run gcc replace_sim.c  -o replace_sim.exe, then after that run the command .\replace_sim.exe, then record the output.
3.	To answer the question: does the parent’s process end quickly? Yes the parent ends quickly after the child process finishes.
VII. Managing Process in Powershell
1.	In the Powershell, call the parent PID, then run Get-Process child_echo  to view running child processes. Next run Stop-process –Id <PID> to terminate the child PID.

VIII. Pushing into Github
1.	Create a repository and named it OS_LA1_ProcessMgmt_Lastname with a README.md
2.	After creating it, GitHub will show you a page with instructions. Copy the HTTPS URL, it looks like: https://github.com/YourUsername/OS_LA1_ProcessMgmt_Lastname.git
3.	Run the following command in Powershell:
o	git remote add origin https://github.com/YourUsername/OS_LA1_ProcessMgmt_Lastname.git
o	git branch -M main
o	git push -u origin main
	

