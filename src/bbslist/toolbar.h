// ライセンス: GPL2

// ツールバーのクラス

#ifndef _BBSLIST_TOOLBAR_H
#define _BBSLIST_TOOLBAR_H

#include <gtkmm.h>

#include "skeleton/toolbar.h"
#include "skeleton/jdtoolbar.h"
#include "skeleton/toolmenubutton.h"

namespace BBSLIST
{
    class BBSListToolBar : public SKELETON::ToolBar
    {
        // ラベルバー
        SKELETON::JDToolbar m_tool_label;

        Gtk::Label m_label;
        SKELETON::ToolMenuButton m_button_toggle;

        SKELETON::ImgToolButton* m_button_check_update_root;
        SKELETON::ImgToolButton* m_button_check_update_open_root;
        Gtk::ToolItem* m_button_stop_check_update;

      public:

        BBSListToolBar();
        virtual ~BBSListToolBar(){}

        // タブが切り替わった時にDragableNoteBookから呼び出される( Viewの情報を取得する )
        virtual void set_view( SKELETON::View * view );

      protected:

        virtual void pack_buttons();

      private:

        void slot_toggle( const int i );
        bool slot_scroll_event( GdkEventScroll* event );
        void slot_check_update_root();
        void slot_check_update_open_root();
    };


    ///////////////////////////////////////

    // 編集ウィンドウのツールバー
    class EditListToolBar : public SKELETON::ToolBar
    {
        // ボタン等のシグナルに直接コネクトする
        friend class EditListWin;

      public:

        EditListToolBar();
        virtual ~EditListToolBar(){}

      protected:

        virtual void pack_buttons();
    };


}


#endif
