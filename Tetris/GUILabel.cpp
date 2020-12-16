#include "GUILabel.hpp"

#include "Renderer.hpp"

#include <sstream>
#include <cctype>

GUILabel::GUILabel(Vec2 const& pos,Vec2 const& size,std::string const&content)
{
    setContent(content);
    this->pos = pos;
    this->size = size;
    singleLine = false;
}
GUILabel::GUILabel()
{

}

void GUILabel::setSingleLine(bool singleLine)
{
    this->singleLine = singleLine;
}
bool GUILabel::isSingleLine()const
{
    return singleLine;
}
void GUILabel::setCenter(bool center)
{
    this->center = center;
}
bool GUILabel::isCenter()const
{
    return center;
}
void GUILabel::setContent(std::string const& content)
{
    splitContent.clear();
    label = content;
    if(singleLine)
    {
        splitContent.push_back(content);
    }
    else
    {
        std::vector<std::string>& words = splitContent;
        std::string this_word;
        int length = label.length();
        for(int i = 0;i < length;++i)
        {
            char this_char = label[i];
            if(isalpha(this_char))
            {
                this_word += this_char;
            }
            else
            {
                if(this_word.length() != 0)
                    words.push_back(this_word);
                this_word = "";
                words.push_back(std::string(this_char,1));
            }
        }
        if(this_word.length() != 0)
            words.push_back(this_word);
    }
}
void GUILabel::draw(Renderer& renderer)
{
    renderer.setColor(color);
    int startx = pos.x;
    int starty = pos.y;
    //int endx = pos.x + size.x;
    //int endy = pos.y + size.y;
    int sizex = size.x;
    int sizey = size.y;
    int textHeight = renderer.getTextHeight(label.c_str());
    if(singleLine)
    {
        if(textHeight > sizey)
            return;
        int textWidth = renderer.getTextWidth(label.c_str());
        if(textWidth > sizex)
        {
            if(renderer.getTextWidth("...") > sizex)
                return;
            int l = 0;
            int r = label.length();
            int mid = (l + r) / 2;
            while(r >= l)
            {
                mid = (l + r) / 2;
                std::string substr = label.substr(0,mid) + "...";
                int newWidth = renderer.getTextWidth(substr.c_str());
                if(newWidth > sizex)
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            std::string ans = label.substr(0,mid) + "...";
            if(center)
            {
                int textWidth = renderer.getTextWidth(ans.c_str());
                int drawy = starty + (sizey - textHeight) / 2;
                int drawx = startx + (sizex - textWidth) / 2;
                renderer.drawText(drawx,drawy,ans.c_str());
            }
            else
                renderer.drawText(startx,starty,ans.c_str());
        }
        else
        {
            int drawx = startx;
            int drawy = starty;
            if(center)
            {
                drawx = startx + (sizex - textWidth) / 2;
                drawy = starty + (sizey - textHeight) / 2;
            }
            renderer.drawText(drawx,drawy,label.c_str());
        }
    }
    /*else
    {
        int size = splitContent.size();
        std::vector<std::string> newSplitContent;
        std::string thisLine;
        int usedWidth = 0;
        for(int i = 0;i < size;++i)
        {
            int textLength = textwidth(splitContent[i].c_str());
            if(usedWidth + textLength > sizex)
            {
                newSplitContent.push_back(thisLine);
                thisLine = "";
                usedWidth = 0;
                if(textLength > sizex)
                    continue;
            }

            thisLine += splitContent[i];
        }

        int drawx = 0;
        int drawy = 0;
        size = newSplitContent.size();
        int usedHeight = textHeight * size;
        if(usedHeight > sizey)
            drawy = starty;
        else if(center)
            drawy = starty + (sizey - usedHeight) / 2;
        if(size == 1 && center)
            drawx = startx + (sizex - textwidth(newSplitContent[0].c_str())) / 2;
        else
            drawx = startx;
        int drawPointerX = drawx;
        int drawPointerY = drawy;
        for(int i = 0;i < size;++i)
        {
            outtextxy(drawPointerX,drawPointerY,newSplitContent[i].c_str());
            drawPointerY += textHeight;
            if(drawPointerY + textHeight > endy)
                break;
        }
    }*/
}
