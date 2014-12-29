#include <a_samp>
#include <L_ColorEmbed>
#include <zcmd>

public OnPlayerText(playerid, text[])
{
	new
	    temp_String[160], temp_GString[160];
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));
	//Setting it's starting point to be as "~w~".
	strcat((temp_GString[0] = '\0', temp_GString[0] = '~', temp_GString[1] = 'w', temp_GString[2] = '~', temp_GString), text, sizeof(temp_GString));
	GameTextForAll(NickHighlight_TextEx(temp_GString, "~w~", "~y~", false), 3000, 3);
	format(temp_String, sizeof(temp_String), "%s", NickHighlight_SCMEx(temp_String, "{FFFFFF}", false, "{FF0000}"));
	SendPlayerMessageToAll(playerid, ColorEmbed_SCM(temp_String));
	return 0; 
}

CMD:dialogtest(playerid, params[])
{
	if(isnull(params)) return 0;
	new
	    temp_String[144];
	strcat((temp_String[0] = '\0', temp_String), params, sizeof(temp_String));
	return ShowPlayerDialog(playerid, 1, DIALOG_STYLE_MSGBOX, "L_ColorEmbed - Test", ColorEmbed_Dialog(temp_String), "OK", "");
}

CMD:displaywords(playerid, params[])
{
	if(isnull(params)) return 0;
	new
	    temp_String[144],
		WORDS[][] = {"Lordzy", "KaperStone", "XKIRIL"};
	strcat((temp_String[0] = '\0', temp_String), params, sizeof(temp_String));
	SendClientMessageToAll(-1, WordsHighlight_SCMEx(temp_String, "{FFFFFF}", "{FF0000}", WORDS, false, sizeof(WORDS)));
	return 1;
}
