// ライセンス: GPL2

//
// 個別の板の管理クラス
//
#ifndef _BOARDADMIN_H
#define _BOARDADMIN_H

#include "skeleton/admin.h"

#include "sign.h"

#include <string>

namespace BOARD
{
    class BoardToolBar;

    class BoardAdmin : public SKELETON::Admin
    {
        BoardToolBar* m_toolbar;

      public:
        BoardAdmin( const std::string& url );
        ~BoardAdmin();

        virtual void save_session();

      protected:

        virtual COMMAND_ARGS get_open_list_args( const std::string& url, const COMMAND_ARGS& command_list );
        virtual SKELETON::View* create_view( const COMMAND_ARGS& command );

        // view_modeに該当するページを探す
        virtual int find_view( const std::string& view_mode );

        // ツールバー
        virtual void show_toolbar();
        virtual void toggle_toolbar();
        virtual void open_searchbar();
        virtual void close_searchbar();

        virtual void command_local( const COMMAND_ARGS& command );

        virtual void restore( const bool only_locked );
        virtual COMMAND_ARGS url_to_openarg( const std::string& url, const bool tab, const bool lock );
        virtual const std::string command_to_url( const COMMAND_ARGS& command );

        virtual void switch_admin();

        virtual void restore_lasttab();

      private:

        // タブをお気に入りにドロップした時にお気に入りがデータ送信を要求してきた
        virtual void slot_drag_data_get( Gtk::SelectionData& selection_data, const int page );
    };
    
    BoardAdmin* get_admin();
    void delete_admin();
}

#endif
