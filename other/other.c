#if 0
			INT iCurEdit;
			INT iOffset;

			iCurEdit = pEdit->m_iCurEdit-iStrOffset;
			iOffset = iStrOffset;
			while(TRUE)
			{
				iStrOffset = MaxFullPrintAsc8x16(&bufferRect, pEdit->m_string.m_pcVal+iOffset, iCurEdit);
				if(iCurEdit == iStrOffset)
				{//��Ч��ʾλ�á�
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
			{//���֣���ʾ����С��һ���ַ�����Ч���ο�
				TextOut8X16ERectBuffer(pLocalScreen, 0, 0, &bufferRect, pEdit->m_string.m_pcVal+iOffset, pWin->m_font.m_color, 0);
			}
#endif

