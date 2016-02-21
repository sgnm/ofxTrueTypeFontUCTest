//
//  lyrics.h
//  ofxTrueTypeFontUCTest
//
//  Created by Shin on 2/21/16.
//
//

#ifndef ofxTrueTypeFontUCTest_Lyrics_h
#define ofxTrueTypeFontUCTest_Lyrics_h

class Lyrics{
private:
    const vector<string> _lyrics = {
        "厚岸",
        "国縫",
        "上雷",
        "川汲",
        "住初",
        "登別",
        "上湧別",
        "旭神",
        "歌内",
        "下川",
        "剣淵",
        "和寒",
        "厚床",
        "長万部",
        "馬主来",
        "散布",
        "来岸",
        "倶知安",
        "鍛高",
        "奔幌戸",
        "北兵村",
        "南幌",
        "抜海",
        "幌満",
        "力昼",
        "寧楽",
        "別狩",
        "樽真布",
    };
    
public:
    string _str;
    
    string getNextString(){
        static int i = 0;
        if(i >= _lyrics.size()) i = 0;
        _str = _lyrics.at(i);
        i++;
        return _str;
    }
    
    const vector<string> circleLyrics = {
        "厚","岸","国","縫","上","雷","川","汲","住","初","登","別","上","湧","別","旭","神",
    };
};


#endif
