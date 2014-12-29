/*______________________________________________________________________________

							L_ColorEmbed - v1.0
								 By
							   Lordzy


This include allows you to embed colors and highlight marked words on a string
which can be used for client-messages, gametexts, textdraws and even for dialogs.
It also contains in-built functions to highlight player names for using it on
client message/dialogs and for gametexts/textdraws.

Further information about this include can be found on it's release topic at
SA-MP forums!

LICENSE:

      This Source Code Form is subject to the
      terms of the Mozilla Public License, v.
      2.0. If a copy of the MPL was not
      distributed with this file, You can
      obtain one at
      http://mozilla.org/MPL/2.0/.


Natives:

native NickHighlight_SCM(text[], scmcol[9], bool:ignorecase = false, hcol[9] = "\0");
native NickHighlight_SCMEx(text[], scmcol[9], bool:ignorecase = false, hcol[9] = "\0");
native NickHighlight_Text(text[], txcol[], hcol[], bool:ignorecase = false);
native NickHighlight_TextEx(text[], txcol[], hcol[], bool:ignorecase = false);
native WordsHighlight_SCM(text[], scmcol[9], hcol[9], words[][], bool:ignorecase = false, size = sizeof(words));
native WordsHighlight_SCMEx(text[], scmcol[9], hcol[9], words[][], bool:ignorecase = false, size = sizeof(words));
native WordsHighlight_Text(text[], txcol[], hcol[], words[][], bool:ignorecase = false, size = sizeof(words));
native WordsHighlight_TextEx(text[], txcol[], hcol[], words[][], bool:ignorecase = false, size = sizeof(words));
native ColorEmbed_SCM(text[], rchar = 'x', size = sizeof(text));
native ColorEmbed_Dialog(text[], rchar = 'x', size = sizeof(text));




================================================================================    */

#if defined _included_L_ColorEmbed
	#endinput
#endif

#define _included_L_ColorEmbed

/*

Parameters for both NickHighlight_SCM and NickHighlight_SCMEx

text[] = The text that has to be formatted.
scmcol[] = The color that the client message has got, usually for chat, it's white {FFFFFF}
ignorecase = If it's set to false, names will be highlighted on text only if it's exactly like how the player's nick is.
hcol[] = The highlight color to be displayed, if it's not set, GetPlayerColor will be used instead.

The difference between NickHighlight_SCM and NickHighlight_SCMEx is that if the 'text' repeats
the highlighted player's name, the latter one will highlight that too where as the first one will highlight
only once.

*/



stock NickHighlight_SCM(text[], scmcol[9], bool:ignorecase = false, hcol[9] = "\0")
{
	new
		temp_String[150],
		temp_Pos = -1,
		temp_Nick[MAX_PLAYER_NAME],
		temp_pCol[10];
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0, j = GetMaxPlayers(); i< j; i++)
	{
	    if(!IsPlayerConnected(i))
 			continue;
		GetPlayerName(i, temp_Nick, MAX_PLAYER_NAME);
		temp_Pos = strfind(temp_String, temp_Nick, ignorecase, 0);

		if(temp_Pos != -1)
		{
		    if(hcol[0] == '\0')
		    {
				format(temp_pCol, sizeof(temp_pCol), "{%06x}", GetPlayerColor(i) >>> 8);
				strins(temp_String, temp_pCol, temp_Pos, sizeof(temp_String));
			}
			else
			{
			    strins(temp_String, hcol, temp_Pos, sizeof(temp_String));
			}

			strins(temp_String, scmcol, temp_Pos + strlen(temp_Nick) + 8, sizeof(temp_String));
		}
		else continue;
	}
	return temp_String;
}

stock NickHighlight_SCMEx(text[], scmcol[9], bool:ignorecase = false, hcol[9] = "\0")
{
	new
	    temp_String[150],
	    temp_Pos = -1,
	    temp_NewPos = 0,
	    temp_Nick[MAX_PLAYER_NAME],
		temp_pCol[10];
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0, j = GetMaxPlayers(); i< j; i++)
	{
	    if(!IsPlayerConnected(i)) continue;
	    GetPlayerName(i, temp_Nick, sizeof(temp_Nick));
	    temp_Pos = strfind(temp_String, temp_Nick, ignorecase, 0);

	    while(temp_Pos != -1)
	    {
	        if(hcol[0] == '\0')
	        {
				format(temp_pCol, sizeof(temp_pCol), "{%06x}", GetPlayerColor(i));
				strins(temp_String, temp_pCol, temp_Pos, sizeof(temp_String));
			}
			else
			{
			    strins(temp_String, hcol, temp_Pos, sizeof(temp_String));
			}
			temp_NewPos = temp_Pos + strlen(temp_Nick) + 8;
			strins(temp_String, scmcol, temp_NewPos, sizeof(temp_String));
			temp_NewPos += 8;
			temp_Pos = strfind(temp_String, temp_Nick, ignorecase, temp_NewPos);
		}
	}
	return temp_String;
}

/*

Parameters for both NickHighlight_Text and NickHighlight_TextEx

text[] = The text that has to be formatted.
txcol[] = The default color of the text. Suppose if the starting color is "~g~", txcol should also be "~g~"
hcol[] = The color used for highlighting.
ignorecase = Similar to the above function's, checks for case sensitive.

*/

stock NickHighlight_Text(text[], txcol[], hcol[], bool:ignorecase = false)
{
	new
	    temp_String[256],
	    temp_Pos = -1,
	    temp_Nick[MAX_PLAYER_NAME];
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0, j = GetMaxPlayers(); i< j; i++)
	{
	    if(!IsPlayerConnected(i))
	        continue;
		GetPlayerName(i, temp_Nick, MAX_PLAYER_NAME);
		temp_Pos = strfind(temp_String, temp_Nick, ignorecase, 0);

		if(temp_Pos != -1)
		{
		    strins(temp_String, txcol, temp_Pos + strlen(temp_Nick), sizeof(temp_String));
		    strins(temp_String, hcol, temp_Pos, sizeof(temp_String));
		}
		else continue;
	}
	return temp_String;
}

stock NickHighlight_TextEx(text[], txcol[], hcol[], bool:ignorecase = false)
{
	new
	    temp_String[256],
	    temp_Pos = -1,
	    temp_NewPos = 0,
	    temp_Nick[MAX_PLAYER_NAME];
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0, j = GetMaxPlayers(); i< j; i++)
	{
	    if(!IsPlayerConnected(i))
	        continue;
		GetPlayerName(i, temp_Nick, sizeof(temp_Nick));
		temp_Pos = strfind(temp_String, temp_Nick, ignorecase, 0);

		while(temp_Pos != -1)
		{
		    temp_NewPos = temp_Pos + strlen(temp_Nick);
		    strins(temp_String, txcol, temp_NewPos, sizeof(temp_String));
			strins(temp_String, hcol, temp_Pos, sizeof(temp_String));
			temp_NewPos += strlen(txcol) + strlen(hcol);
			temp_Pos = strfind(temp_String, temp_Nick, ignorecase, temp_NewPos);
		}
	}
	return temp_String;
}

/*

Parameters for WordsHighlight_SCM and WordsHighlight_SCMEx

text[] = The text to be formatted.
scmcol[] = Default color of the client message.
hcol[] = The color that's used for highlighting.
words[][] = Words to be highlighted.
ignorecase = Whether to ignore case sensitivity or not.
size = Number of words.

Example:

new
	WORDS[][] = {"Function", "This", "Testing"};
WordsHighlight_SCM(text, "{FFFFFF}", "{FF0000}", WORDS, false, 3);

*/

stock WordsHighlight_SCM(text[], scmcol[9], hcol[9], words[][], bool:ignorecase = false, size = sizeof(words))
{
	new
	    temp_String[150],
	    temp_Pos = -1;
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0; i< size; i++)
	{
	    temp_Pos = strfind(temp_String, words[i], ignorecase, 0);
	    if(temp_Pos != -1)
	    {
	        strins(temp_String, hcol, temp_Pos, sizeof(temp_String));
       		strins(temp_String, scmcol, temp_Pos + strlen(words[i]) + 8, sizeof(temp_String));
		}
		else continue;

	}
	return temp_String;
}

stock WordsHighlight_SCMEx(text[], scmcol[9], hcol[9], words[][], bool:ignorecase = false, size = sizeof(words))
{
	new
	    temp_String[150],
	    temp_Pos = -1,
		temp_NewPos = 0,
		temp_WordLen;
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0; i< size; i++)
	{
		temp_Pos = strfind(temp_String, words[i], ignorecase, 0);
		temp_WordLen = strlen(words[i]);

		while(temp_Pos != -1)
		{
		    strins(temp_String, hcol, temp_Pos, sizeof(temp_String)); 
		    strins(temp_String, scmcol, temp_Pos + temp_WordLen + 8, sizeof(temp_String));
		    temp_NewPos = temp_Pos + temp_WordLen + 16;
		    temp_Pos = strfind(temp_String, words[i], ignorecase, temp_NewPos);
		}
	}
	return temp_String;
}
/*

Parameters:

text[] = The text that has to be formatted.
txcol[] = The default color of the text.
hcol[] = The color that has to be used for highlighting.
words[][] = The words that has to be highlighted.
ignorecase = Whether case sensitivity has to be ignored or not.
size = Number of words.

Example:
new
	WORDS[][] = {"This", "Function", "Testing"};
WordsHighlight_Text(text, "~g~", "~h~~r~", WORDS, false, sizeof(words));

*/

stock WordsHighlight_Text(text[], txcol[], hcol[], words[][], bool:ignorecase = false, size = sizeof(words))
{
	new
	    temp_String[256],
	    temp_Pos = -1;
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0; i< size; i++)
	{
	    temp_Pos = strfind(temp_String, words[i], ignorecase, 0);
	    if(temp_Pos != -1)
	    {
	        strins(temp_String, txcol, temp_Pos + strlen(words[i]), sizeof(temp_String));
	        strins(temp_String, hcol, temp_Pos, sizeof(temp_String));
		}
		else continue;
	}
	return temp_String;
}

stock WordsHighlight_TextEx(text[], txcol[], hcol[], words[][], bool:ignorecase = false, size = sizeof(words))
{
	new
	    temp_String[256],
	    temp_Pos = -1,
	    temp_NewPos = 0,
		temp_WordLen;
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0; i< size; i++)
	{
	    temp_Pos = strfind(temp_String, words[i], ignorecase, 0);
	    temp_WordLen = strlen(words[i]);

	    while(temp_Pos != -1)
	    {
	        strins(temp_String, txcol, temp_Pos + temp_WordLen, sizeof(temp_String));
	        strins(temp_String, hcol, temp_Pos, sizeof(temp_String));
	        temp_NewPos = temp_Pos + temp_WordLen + strlen(hcol) + strlen(txcol);
	        temp_Pos = strfind(temp_String, words[i], ignorecase, temp_NewPos);
		}
	}
	return temp_String;
}

/*

Parameters:

text[] = The text to be color embedded.
rchar = The string that has to indicate color embedding, eg : {xFF0000} - If this is found when rchar = 'x', then
		color embedding will take place and it will be replaced as  {FF0000}
size = size of the text.

ColorEmbed_SCM is used for client messages and ColorEmbed_Dialog is used for
dialog caption. The latter one also formats "\n" and forms a new line if found.

*/
stock ColorEmbed_SCM(text[], rchar = 'x', size = sizeof(text))
{
	new
	    temp_String[144];
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0, j = strlen(temp_String); i< j; i++)
	{
	    if(temp_String[i] == '{' && i+1 < size)
	    {
	        if(temp_String[i+1] == rchar)
	        {
	        	if(i + 8 < size)
	        	{
	            	if(temp_String[i+8] == '}')
	            	{
						strdel(temp_String, i+1, i+2);
					}
				}
			}
		}
	}
	return temp_String;
}

stock ColorEmbed_Dialog(text[], rchar = 'x', size = sizeof(text))
{
	new
	    temp_String[256];
	strcat((temp_String[0] = '\0', temp_String), text, sizeof(temp_String));

	for(new i = 0, j = strlen(temp_String); i< j; i++)
	{
	    if(temp_String[i] == '{' && i+1 < size)
	    {
	        if(temp_String[i+1] == rchar)
	        {
	            if(i + 8 < size)
	            {
	                if(temp_String[i+8] == '}')
	                {
	                    strdel(temp_String, i+1, i+2);
					}
				}
			}
		}
		else if(temp_String[i] == '\\' && i+1 < size)
		{
		    if(temp_String[i+1] == 'n')
		    {
		        strdel(temp_String, i, i+1);
		        temp_String[i] = '\n';
			}
		}
	}
	return temp_String;
}


