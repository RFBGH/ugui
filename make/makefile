objects = main.o Mem.o Log.o Color.o Malloc.o RndGen.o BmpTool.o \
		  Screen.o DrawLine.o res.o TextOut.o DrawRect.o List.o  \
		  OnWinMsgProcList.o Window.o WinTree.o WinBase.o WinMsg.o\
		  Font.o Brush.o smath.o GdiCom.o Button.o SimString.o \
		  EditView.o DrawBmp.o CheckBox.o SimCalc.o 

CFLAGS += -I ../Comm -I ../Adapt -I ../Tool -I ../CFG -I ../GDI -I ../GDI/res \
		  -I ../GUI -I ../Widget
CFLAGS += -g
CC = gcc
target = main

main: $(objects)
	$(CC) -o $(target) $(objects)

main.o: ../main.c
	$(CC) $(CFLAGS) -c ../main.c

Mem.o: ../Tool/Mem.c
	$(CC) $(CFLAGS) -c ../Tool/Mem.c

Log.o: ../Tool/Log.c
	$(CC) $(CFLAGS) -c ../Tool/Log.c

Malloc.o: ../Tool/Malloc.c
	$(CC) $(CFLAGS) -c ../Tool/Malloc.c

smath.o: ../Tool/smath.c
	$(CC) $(CFLAGS) -c ../Tool/smath.c

List.o: ../Tool/List.c
	$(CC) $(CFLAGS) -c ../Tool/List.c

RndGen.o: ../Tool/RndGen.c
	$(CC) $(CFLAGS) -c ../Tool/RndGen.c

BmpTool.o: ../Tool/BmpTool.c
	$(CC) $(CFLAGS) -c ../Tool/BmpTool.c

SimString.o: ../Tool/SimString.c
	$(CC) $(CFLAGS) -c ../Tool/SimString.c

Color.o: ../Adapt/Color.c
	$(CC) $(CFLAGS) -c ../Adapt/Color.c

Screen.o: ../Adapt/Screen.c
	$(CC) $(CFLAGS) -c ../Adapt/Screen.c

DrawLine.o: ../GDI/DrawLine.c
	$(CC) $(CFLAGS) -c ../GDI/DrawLine.c

res.o: ../GDI/res/res.c
	$(CC) $(CFLAGS) -c ../GDI/res/res.c

DrawBmp.o: ../GDI/DrawBmp.c
	$(CC) $(CFLAGS) -c ../GDI/DrawBmp.c

TextOut.o: ../GDI/TextOut.c
	$(CC) $(CFLAGS) -c ../GDI/TextOut.c

DrawRect.o: ../GDI/DrawRect.c
	$(CC) $(CFLAGS) -c ../GDI/DrawRect.c

Font.o: ../GDI/Font.c
	$(CC) $(CFLAGS) -c ../GDI/Font.c

GdiCom.o: ../GDI/GdiCom.c
	$(CC) $(CFLAGS) -c ../GDI/GdiCom.c

Brush.o: ../GDI/Brush.c
	$(CC) $(CFLAGS) -c ../GDI/Brush.c

Window.o: ../GUI/Window.c
	$(CC) $(CFLAGS) -c ../GUI/Window.c

WinTree.o: ../GUI/WinTree.c
	$(CC) $(CFLAGS) -c ../GUI/WinTree.c

WinBase.o: ../GUI/WinBase.c
	$(CC) $(CFLAGS) -c ../GUI/WinBase.c

WinMsg.o: ../GUI/WinMsg.c
	$(CC) $(CFLAGS) -c ../GUI/WinMsg.c

OnWinMsgProcList.o: ../GUI/OnWinMsgProcList.c
	$(CC) $(CFLAGS) -c ../GUI/OnWinMsgProcList.c

Button.o: ../Widget/Button.c
	$(CC) $(CFLAGS) -c ../Widget/Button.c

EditView.o: ../Widget/EditView.c
	$(CC) $(CFLAGS) -c ../Widget/EditView.c

CheckBox.o: ../Widget/CheckBox.c
	$(CC) $(CFLAGS) -c ../Widget/CheckBox.c

SimCalc.o: ../AppTest/Calc/SimCalc.c
	$(CC) $(CFLAGS) -c ../AppTest/Calc/SimCalc.c

#CalcAlgor.o: ../AppTest/Calc/SimCalc.c
#	$(CC) $(CFLAGS) -c ../AppTest/CalcAlgor.c

.PHONEY : clean
clean:
	rm $(target).exe $(objects)

backup:
	cp main.exe main.exe.bk

