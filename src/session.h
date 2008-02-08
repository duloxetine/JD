// ライセンス: GPL2
//
// 座標などのウィンドウ情報とかのセッション情報
//

#ifndef _SESSION_H
#define _SESSION_H

#include <list>
#include <vector>
#include <string>

namespace SESSION
{
    // focused_admin の値。どこにフォーカスしているか
    // Core::slot_focus_in_event, Core::slot_focus_out_event などを参照
    enum
    {
        FOCUS_SIDEBAR = 0,
        FOCUS_BOARD,
        FOCUS_ARTICLE,
        FOCUS_IMAGE,
        FOCUS_MESSAGE,
        FOCUS_NO
    };

    // ペーンモード
    enum
    {
        MODE_2PANE = 0,
        MODE_3PANE,
        MODE_V3PANE
    };


    // ツールバーの位置
    enum
    {
        TOOLBAR_NORMAL = 0,
        TOOLBAR_RIGHT,

        TOOLBAR_NO
    };

    // WM
    enum
    {
        WM_GNOME = 0,
        WM_XFCE,
        WM_KDE,
        WM_UNKNON
    };

    void init_session();
    void save_session();

    // ブート中
    const bool is_booting();
    void set_booting( bool boot );

    // 終了中
    const bool is_quitting();
    void set_quitting( bool quit );

    const std::string& get_distribution_name();

    const int get_wm();

    const int get_mode_pane();
    void set_mode_pane( int mode );
    
    const bool is_online();
    void set_online( bool mode );

    // 2chログイン中
    const bool login2ch();
    void set_login2ch( bool login );

    // BEログイン中
    const bool loginbe();
    void set_loginbe( bool login );

    // サイドバー表示中
    const bool show_sidebar();
    void set_show_sidebar( bool showbar );

    // メニューバー
    const bool show_menubar();
    void set_show_menubar( bool show );

    // ツールバー位置
    const int toolbar_pos();
    void set_toolbar_pos( int pos );

    // 板一覧のツールバー表示
    const bool get_show_bbslist_toolbar();
    void set_show_bbslist_toolbar( bool show );

    // スレ一覧のツールバー表示
    const bool get_show_board_toolbar();
    void set_show_board_toolbar( bool show );

    // スレビューのツールバー表示
    const bool get_show_article_toolbar();
    void set_show_article_toolbar( bool show );

    // スレ一覧のタブ表示
    const bool get_show_board_tab();
    void set_show_board_tab( bool show );

    // スレビューのタブ
    const bool get_show_article_tab();
    void set_show_article_tab( bool show );

    // フォーカスされているadmin
    const int focused_admin();
    void set_focused_admin( int admin );


    // 各windowの座標
    const int get_x_win_main(); // メインウィンドウ
    const int get_y_win_main();
    void set_x_win_main( int x );
    void set_y_win_main( int y );

    const int get_x_win_img(); // 画像ウィンドウ
    const int get_y_win_img();
    void set_x_win_img( int x );
    void set_y_win_img( int y );

    const int get_x_win_mes(); // 書き込みウィンドウ
    const int get_y_win_mes();
    void set_x_win_mes( int x );
    void set_y_win_mes( int y );


    // 各windowのサイズ
    const int get_width_win_main(); // メインウィンドウ
    const int get_height_win_main();
    void set_width_win_main( int width );
    void set_height_win_main( int height );

    const int get_width_win_img(); // 画像ウィンドウ
    const int get_height_win_img();
    void set_width_win_img( int width );
    void set_height_win_img( int height );

    const int get_width_win_mes(); // 書き込みウィンドウ
    const int get_height_win_mes();
    void set_width_win_mes( int width );
    void set_height_win_mes( int height );


    // 各window がフォーカスされているか
    const bool is_focus_win_main(); // メインウィンドウ
    void set_focus_win_main( bool set );

    const bool is_focus_win_img(); // 画像ウィンドウ
    void set_focus_win_img( bool set );

    const bool is_focus_win_mes(); // 書き込みウィンドウ
    void set_focus_win_mes( bool set );


    // 各window が最大化されているか
    const bool is_maximized_win_main(); // メインウィンドウ
    void set_maximized_win_main( bool maximized );

    const bool is_maximized_win_img(); // 画像ウィンドウ
    void set_maximized_win_img( bool set );

    bool is_maximized_win_mes(); // 書き込みウィンドウ
    void set_maximized_win_mes( bool maximized );


    // 各window が最小化されているか
    const bool is_iconified_win_main(); // メインウィンドウ
    void set_iconified_win_main( bool set );

    const bool is_iconified_win_img(); // 画像ウィンドウ
    void set_iconified_win_img( bool set );

    const bool is_iconified_win_mes(); // 書き込みウィンドウ
    void set_iconified_win_mes( bool set );


    // 各window が画面に表示されているか
    const bool is_shown_win_main(); // メインウィンドウ
    void set_shown_win_main( bool set );

    const bool is_shown_win_img(); // 画像ウィンドウ
    void set_shown_win_img( bool set );

    const bool is_shown_win_mes(); // 書き込みウィンドウ
    void set_shown_win_mes( bool set );



    // ダイアログ表示中
    const bool is_dialog_shown();
    void set_dialog_shown( bool set );

    // サイドバーを閉じる前にフォーカスされていたadmin
    int focused_admin_sidebar();
    void set_focused_admin_sidebar( int admin );

    /// メインウィンドウのペインの敷居の位置
    int hpane_main_pos();
    int vpane_main_pos();
    int hpane_main_r_pos();
    int vpane_main_mes_pos();
    void set_hpane_main_pos( int pos );
    void set_vpane_main_pos( int pos );
    void set_hpane_main_r_pos( int pos );
    void set_vpane_main_mes_pos( int pos );

    // 前回閉じたときに開いていたメインnotebookのページ番号
    int notebook_main_page();
    void set_notebook_main_page( int page );

    // 前回閉じたときに開いていたbbslistの開いてるページ番号
    int bbslist_page();
    void set_bbslist_page( int page );


    // 前回閉じたときに開いていたスレ一覧のページ番号とURL
    int board_page();
    void set_board_page( int page );
    std::list< std::string >& get_board_URLs();
    void set_board_URLs( const std::list< std::string >& urls );

    // スレ一覧のロック状態
    const std::list< bool >& get_board_locked();
    void set_board_locked( const std::list< bool >& locked );

    // 前回閉じたときに開いていたスレタブのページ番号とURL
    int article_page();
    void set_article_page( int page );
    std::list< std::string >& get_article_URLs();
    void set_article_URLs( const std::list< std::string >& urls );

    // スレタブのロック状態
    const std::list< bool >& get_article_locked();
    void set_article_locked( const std::list< bool >& locked );

    // 前回閉じたときに開いていたimageのページ番号とURL
    int image_page();
    void set_image_page( int page );
    const std::list< std::string >& image_URLs();
    void set_image_URLs( const std::list< std::string >& urls );

    // 画像タブのロック状態
    const std::list< bool >& get_image_locked();
    void set_image_locked( const std::list< bool >& locked );

    // 現在開いている bbslist のページ
    const int get_bbslist_current_page();

    // 現在開いている bbslist のurl
    const std::string get_bbslist_current_url();

    // サイドバーのツールバー項目
    const std::string& get_items_sidebar_str();
    void set_items_sidebar_str( const std::string& items );
    const int get_item_sidebar( const int num );

    // メインツールバーの項目
    const std::string& get_items_main_toolbar_str();
    void set_items_main_toolbar_str( const std::string& items_str );
    const int get_item_main_toolbar( const int num );

    // スレビューのツールバーの項目
    const std::string& get_items_article_toolbar_str();
    void set_items_article_toolbar_str( const std::string& items_str );
    const int get_item_article_toolbar( const int num );

    // スレ一覧のツールバー項目
    const std::string& get_items_board_toolbar_str();
    void set_items_board_toolbar_str( const std::string& items );
    const int get_item_board_toolbar( const int num );

    // スレ一覧の項目
    const std::string& get_items_board_str();
    void set_items_board_str( const std::string& items );
    const int get_item_board( const int num );

    // 書き込みビューのツールバー項目
    const std::string& get_items_msg_toolbar_str();
    void set_items_msg_toolbar_str( const std::string& items );
    const int get_item_msg_toolbar( const int num );

    // スレ一覧の列幅
    int col_mark();
    int col_id();
    int col_subject();
    int col_number();
    int col_load();
    int col_new();
    int col_since();
    int col_write();
    int col_speed();
    void set_col_mark( int width );
    void set_col_id( int width );
    void set_col_subject( int width );
    void set_col_number( int width );
    void set_col_load( int width );
    void set_col_new( int width );
    void set_col_since( int width );
    void set_col_write( int width );
    void set_col_speed( int width );


    // 現在開いているarticle のurl
    const std::string get_article_current_url();


    // 埋め込みimage使用
    bool get_embedded_img();
    void set_embedded_img( bool set );


    // 埋め込みmessageを使用
    bool get_embedded_mes();
    void set_embedded_mes( bool set );

    // 書き込み後にmessageを閉じる
    bool get_close_mes();
    void set_close_mes( bool set );


    // 最後にdatを保存したディレクトリ
    const std::string& dir_dat_save();
    void set_dir_dat_save( const std::string& dir );

    // 最後に画像を保存したディレクトリ
    const std::string& dir_img_save();
    void set_dir_img_save( const std::string& dir );

    // 下書きファイルのディレクトリ
    const std::string& get_dir_draft();
    void set_dir_draft( const std::string& dir );

    // ポップアップメニュー表示中
    const bool is_popupmenu_shown();
    void set_popupmenu_shown( bool shown );
}

#endif
