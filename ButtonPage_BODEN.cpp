#include "ButtonPage_BODEN.h"

CButtonPage_BODEN::CButtonPage_BODEN(CBrushmanager* brushmanager)
{
	this->brushManager = brushmanager;
	GenerateButtons();
	temp_Button = NULL;
}


void CButtonPage_BODEN::Handle_Klick(ME_MOUSE mouse, int mouseX, int mouseY)
{
	vector<CBrushButton>::iterator it_boden_standard;
	// wenn STRG gedr�ckt wurde, w�hle den Hintergrund aus
	if (mouse == ME_MOUSE_LEFT && KEY_DOWN(ME_KEY_STRG))
	{
		// boden ausw�hlen
		for (it_boden_standard = boden_standard.begin(); it_boden_standard != boden_standard.end(); it_boden_standard++)
		{
			temp_Button = it_boden_standard->SelectBackground(mouseX, mouseY);
			if (temp_Button)
			{
				brushManager->SetGroundId(temp_Button->Get_DrawBrush()->id);
				return;
			}
		}
		return;
	}
	// je nach Button eine andere Farbe ausw�hlen
	SDL_Color temp_color;
	switch (mouse)
	{
	case ME_MOUSE_LEFT:
		temp_color = SDL_RED
		break;
	case ME_MOUSE_MIDDLE:
		temp_color = SDL_YELLOW;
		break;
	case ME_MOUSE_RIGHT:
		temp_color = SDL_CYAN;
		break;
	}

	// versuchen, einen Button auszuw�hlen, wenn ja im Brush-Manager den Brush mappen
	for (it_boden_standard = boden_standard.begin(); it_boden_standard != boden_standard.end(); it_boden_standard++)
	{
		temp_Button = it_boden_standard->SelectTry(mouseX, mouseY, temp_color);
		if (temp_Button)
		{
			brushManager->Map_Mouse_Key(mouse, temp_Button);
			return;
		}
	}
}


void CButtonPage_BODEN::Render()
{
	for (it_boden_standard = boden_standard.begin(); it_boden_standard != boden_standard.end(); it_boden_standard++)
	{
		it_boden_standard->Render();
	}
}


void CButtonPage_BODEN::GenerateButtons()
{
	int boden_y_end = Generate_boden_standard(y_start);
}

// Erzeugt alle Buttons, mit denen man Boden malen kann
// gibt die y-H�he zur�ck
int CButtonPage_BODEN::Generate_boden_standard(int start_y)
{
	int buttonWidth = 45; // mit Rand 49
	int buttonHeight = 45; // mit Rand 49
	int bor_ButtonWidth = buttonWidth + 4;
	int bor_ButtonHeight = buttonHeight + 4;
	int akt_y = start_y;
	int akt_x = x_start;

	// i repr�sentiert die id
	for (int i = 0; i < NUMBODEN; i++)
	{
		// sollte die Buttonreihe aus dem linken Teil herauslaufen wird alles gerichtet
		if (akt_y + bor_ButtonWidth > MOVECAMX)
		{
			akt_y += abstand;
			akt_x = x_start;
		}
		buttonRect = { akt_x, akt_y, buttonWidth, buttonHeight };
		CBrushButton akt_Button = CBrushButton(i * 64, BODEN, buttonRect, g_pLoader->getTexture("T_TEXTURSETMENU"), g_pLoader->getTexture("T_BUTTONBORDER"));
		boden_standard.push_back(akt_Button);
		akt_x += abstand;
	}
	return akt_y;

}