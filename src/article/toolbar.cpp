// ライセンス: GPL2

//#define _DEBUG
#include "jddebug.h"

#include "toolbar.h"
#include "articleadmin.h"

#include "controlutil.h"
#include "controlid.h"
#include "session.h"
#include "global.h"

using namespace ARTICLE;


ArticleToolBar::ArticleToolBar() :
    SKELETON::ToolBar( ARTICLE::get_admin() ),
    m_status( STATUS_NORMAL ),
    m_button_favorite( Gtk::Stock::COPY ),
    m_button_write( ICON::WRITE ),
    m_button_delete( Gtk::Stock::DELETE ),
    m_button_reload( Gtk::Stock::REFRESH ),
    m_button_stop( Gtk::Stock::STOP ),
    m_button_open_search( Gtk::Stock::FIND ),

    m_searchbar_shown( false ),
    m_button_close_search( Gtk::Stock::UNDO ),
    m_button_up_search( Gtk::Stock::GO_UP ),
    m_button_down_search( Gtk::Stock::GO_DOWN ),
    m_button_drawout_and( Gtk::Stock::CUT ),
    m_button_drawout_or( Gtk::Stock::ADD ),
    m_button_clear_hl( Gtk::Stock::CLEAR )
{
    signal_realize().connect( sigc::mem_fun(*this, &ArticleToolBar::slot_realize ) );

    m_label.set_size_request( 0, 0 );
    m_label.set_alignment( Gtk::ALIGN_LEFT );
    m_label.set_selectable( true );
    m_label_ebox.add( m_label );
    m_label_ebox.set_visible_window( false );

    // 検索バー
    set_tooltip( m_button_close_search, CONTROL::get_label_motion( CONTROL::CloseSearchBar ) );
    set_tooltip( m_button_up_search, CONTROL::get_label_motion( CONTROL::SearchPrev ) );
    set_tooltip( m_button_down_search, CONTROL::get_label_motion( CONTROL::SearchNext ) );
    set_tooltip( m_button_drawout_and, CONTROL::get_label_motion( CONTROL::DrawOutAnd ) );
    set_tooltip( m_button_drawout_or, CONTROL::get_label_motion( CONTROL::DrawOutOr ) );
    set_tooltip( m_button_clear_hl, CONTROL::get_label_motion( CONTROL::HiLightOff ) );
    m_searchbar.pack_start( m_entry_search, Gtk::PACK_EXPAND_WIDGET );
    m_searchbar.pack_end( m_button_close_search, Gtk::PACK_SHRINK );
    m_searchbar.pack_end( m_button_clear_hl, Gtk::PACK_SHRINK );
    m_searchbar.pack_end( m_button_drawout_or, Gtk::PACK_SHRINK );
    m_searchbar.pack_end( m_button_drawout_and, Gtk::PACK_SHRINK );
    m_searchbar.pack_end( m_button_up_search, Gtk::PACK_SHRINK );
    m_searchbar.pack_end( m_button_down_search, Gtk::PACK_SHRINK );
    m_entry_search.add_mode( CONTROL::MODE_COMMON );

    pack_buttons();
}
        

//
// ボタンのパッキング
//
void ArticleToolBar::pack_buttons()
{
    int num = 0;
    for(;;){
        int item = SESSION::get_item_article_toolbar( num );
        if( item == ITEM_END ) break;
        switch( item ){

            case ITEM_WRITEMSG:
                get_buttonbar().pack_start( m_button_write, Gtk::PACK_SHRINK );
                set_tooltip( m_button_write, CONTROL::get_label_motion( CONTROL::WriteMessage ) );
                break;

            case ITEM_OPENBOARD:
                m_button_board.set_focus_on_click( false );
                m_button_board.set_relief( Gtk::RELIEF_NONE );
                get_buttonbar().pack_start( m_button_board, Gtk::PACK_SHRINK );
                set_tooltip( m_button_board, CONTROL::get_label_motion( CONTROL::OpenParentBoard ) );
                break;

            case ITEM_NAME:
                get_buttonbar().pack_start( m_label_ebox, Gtk::PACK_EXPAND_WIDGET, 2 );
                break;

            case ITEM_SEARCH:
                get_buttonbar().pack_start( m_button_open_search, Gtk::PACK_SHRINK );
                set_tooltip( m_button_open_search, CONTROL::get_label_motion( CONTROL::Search ) );
                break;

            case ITEM_RELOAD:
                get_buttonbar().pack_start( m_button_reload, Gtk::PACK_SHRINK );
                set_tooltip( m_button_reload, CONTROL::get_label_motion( CONTROL::Reload ) );
                break;

            case ITEM_STOPLOADING:
                get_buttonbar().pack_start( m_button_stop, Gtk::PACK_SHRINK );
                set_tooltip( m_button_stop, CONTROL::get_label_motion( CONTROL::StopLoading ) );
                break;

            case ITEM_FAVORITE:
                get_buttonbar().pack_start( m_button_favorite, Gtk::PACK_SHRINK );
                set_tooltip( m_button_favorite, CONTROL::get_label_motion( CONTROL::AppendFavorite )
                             + "...\n\nスレのタブをお気に入りに直接Ｄ＆Ｄしても登録可能" );
                break;

            case ITEM_DELETE:
                get_buttonbar().pack_start( m_button_delete, Gtk::PACK_SHRINK );
                set_tooltip( m_button_delete, CONTROL::get_label_motion( CONTROL::Delete ) );
                break;

            case ITEM_QUIT:
                get_buttonbar().pack_start( *get_button_close(), Gtk::PACK_SHRINK );
                break;

            case ITEM_PREVVIEW:
                get_buttonbar().pack_start( *get_button_back(), Gtk::PACK_SHRINK );
                break;

            case ITEM_NEXTVIEW:
                get_buttonbar().pack_start( *get_button_forward(), Gtk::PACK_SHRINK );
                break;

            case ITEM_SEPARATOR:
                pack_separator();
                break;
        }
        ++num;
    }

    show_all_children();
}


// 検索バー表示
void ArticleToolBar::show_searchbar()
{
    if( ! m_searchbar_shown ){
        pack_start( m_searchbar, Gtk::PACK_SHRINK );
        show_all_children();
        m_searchbar_shown = true;
        m_entry_search.grab_focus(); 
    }
}

// 検索バーを消す
void ArticleToolBar::hide_searchbar()
{
    if( m_searchbar_shown ){
        remove( m_searchbar );
        show_all_children();
        m_searchbar_shown = false;
    }
}


void ArticleToolBar::set_label( const std::string& label )
{
    m_label.set_text( label );
    set_tooltip( m_label_ebox, label );
}


// realizeしたらラベル(Gtk::Entry)の背景色を変える
void ArticleToolBar::slot_realize()
{
    // realize する前にbroken()やold()が呼び出された
    if( m_status == STATUS_BROKEN ) set_broken();
    else if( m_status == STATUS_OLD ) set_old();
}

// スレが壊れている
void ArticleToolBar::set_broken()
{
    m_status = STATUS_BROKEN;

    m_label_ebox.set_visible_window( true );
    m_label.modify_fg( Gtk::STATE_NORMAL, Gdk::Color( "white" ) );
    m_label_ebox.modify_bg( Gtk::STATE_NORMAL, Gdk::Color( "red" ) );
    m_label_ebox.modify_bg( Gtk::STATE_ACTIVE, Gdk::Color( "red" ) );
}

// DAT落ち
void ArticleToolBar::set_old()
{
    m_status = STATUS_OLD;

    m_label_ebox.set_visible_window( true );
    m_label.modify_fg( Gtk::STATE_NORMAL, Gdk::Color( "white" ) );
    m_label_ebox.modify_bg( Gtk::STATE_NORMAL, Gdk::Color( "blue" ) );
    m_label_ebox.modify_bg( Gtk::STATE_ACTIVE, Gdk::Color( "blue" ) );
}



//////////////////////////////////////////////



SearchToolBar::SearchToolBar() :
    SKELETON::ToolBar( ARTICLE::get_admin() ),
    m_button_reload( Gtk::Stock::REFRESH ),
    m_button_stop( Gtk::Stock::STOP )
{
    pack_buttons();
}


//
// ボタンのパッキング
//
void SearchToolBar::pack_buttons()
{
    get_buttonbar().pack_start( m_entry_search, Gtk::PACK_EXPAND_WIDGET );
    get_buttonbar().pack_end( *get_button_close(), Gtk::PACK_SHRINK );

    get_buttonbar().pack_end( m_button_stop, Gtk::PACK_SHRINK );
    set_tooltip( m_button_stop, "検索中止 " + CONTROL::get_motion( CONTROL::StopLoading ) );

    get_buttonbar().pack_end( m_button_reload, Gtk::PACK_SHRINK );
    set_tooltip( m_button_reload, "再検索 " + CONTROL::get_motion( CONTROL::Reload ) );

    m_entry_search.add_mode( CONTROL::MODE_COMMON );

    show_all_children();
}
