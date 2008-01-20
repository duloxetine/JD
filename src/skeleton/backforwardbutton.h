// ライセンス: GPL2

// 「戻る」「進む」履歴付きボタン

#ifndef _BACKFORWARDBUTTON_H
#define _BACKFORWARDBUTTON_H

#include "imgmenubutton.h"

namespace SKELETON
{
    class BackForwardButton : public SKELETON::ImgMenuButton
    {
        std::string m_url;
        bool m_back;

      public:

        BackForwardButton( const std::string& url, const bool back );

        void set_url( const std::string& url );

      protected:

      // ポップアップメニュー表示
      virtual void show_popupmenu();
    };
}

#endif
