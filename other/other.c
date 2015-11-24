#if 0
			INT iCurEdit;
			INT iOffset;

			iCurEdit = pEdit->m_iCurEdit-iStrOffset;
			iOffset = iStrOffset;
			while(TRUE)
			{
				iStrOffset = MaxFullPrintAsc8x16(&bufferRect, pEdit->m_string.m_pcVal+iOffset, iCurEdit);
				if(iCurEdit == iStrOffset)
				{//有效显示位置。
					break;
				}
				iOffset += iStrOffset;
				iCurEdit -= iStrOffset;
				if(iStrOffset == 0)
				{
					break;
				}
			}

			if(iStrOffset)
			{//区分，显示区域小于一个字符的无效矩形框
				TextOut8X16ERectBuffer(pLocalScreen, 0, 0, &bufferRect, pEdit->m_string.m_pcVal+iOffset, pWin->m_font.m_color, 0);
			}
#endif

