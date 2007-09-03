// ライセンス: GPL2

#ifndef _VIEW_H
#define _VIEW_H

#include <gtkmm.h>
#include <string>

#include "control.h"

namespace SKELETON
{
    // 自分がポップアップviewの時に(ポップアップウィンドウ( SKELETON::PopupWin ) 経由で)
    // 親widgetにhideを依頼するシグナル。PopupWin::PopupWin()でPopupWin::slot_hide_popup()にコネクトされる。
    typedef sigc::signal< void > SIG_HIDE_POPUP;    

    // 自分がポップアップviewでリサイズしたときに、明示的にポップアップウィンドウ( SKELETON::PopupWin )
    // にリサイズを依頼するシグナル。PopupWin::PopupWin()でPopupWin::slot_resize_popup()にコネクトされる。
    typedef sigc::signal< void > SIG_RESIZE_POPUP;
    
    class View : public Gtk::VBox
    {
        SIG_HIDE_POPUP m_sig_hide_popup;
        SIG_RESIZE_POPUP m_sig_resize_popup;

        std::string m_url;

        // クライアント領域の幅、高さ
        int m_width_client;
        int m_height_client;

        // 入力コントローラ
        CONTROL::Control m_control;

        // ポップアップメニュー
        Glib::RefPtr< Gtk::ActionGroup > m_action_group;
        Glib::RefPtr< Gtk::UIManager > m_ui_manager;

        // メインウィンドウのタイトルに表示する文字
        std::string m_title;

        // メインウィンドウのステータスバーに表示する文字
        std::string m_status;

        // true ならマウスジェスチャ使用
        bool m_enable_mg; 

        // オートリロード
        bool m_enable_autoreload; // true ならオートリロード可能(デフォルト:off)
        int m_autoreload_mode; // モード
        int m_autoreload_sec; // 何秒おきにリロードするか
        int m_autoreload_counter; // オートリロード用のカウンタ

        // キーボード数字入力ジャンプ用
        int m_keyjump_counter;
        int m_keyjump_num;

        // ロック状態
        bool m_locked;

      protected:

        // UI
        Glib::RefPtr< Gtk::ActionGroup >& action_group(){ return m_action_group; }
        Glib::RefPtr< Gtk::UIManager >& ui_manager(){ return m_ui_manager; }

        // コントローラ
        CONTROL::Control& get_control(){ return m_control; }

        // タイトル
        void set_title( const std::string& title ){ m_title = title; }

        // ステータス
        void set_status( const std::string& status ){ m_status = status; }

        // マウスジェスチャ
        void set_enable_mg( bool mg ){ m_enable_mg = mg; }
        const bool enable_mg() const { return m_enable_mg; }

        // オートリロードのカウンタをインクリメント
        // 指定秒数を越えたら true を返す
        bool inc_autoreload_counter();

        // オートリロード可能/不可能切替え
        void set_enable_autoreload( bool autoreload ){ m_enable_autoreload = autoreload; }

        // オートリロードのカウンタをリセット
        void reset_autoreload_counter(); 

        // 数字入力ジャンプカウンタのインクリメント
        // 指定秒数を越えたら true を返す
        bool inc_keyjump_counter();

        // 数字入力ジャンプカウンタのリセット
        void reset_keyjump_counter(); 

        // 数字入力ジャンプ用に sig_key_press() から呼び出す
        void release_keyjump_key( int key );

        // ポップアップメニュー表示
        void show_popupmenu( const std::string& url, bool use_slot = false );

        // ポップアップメニュー表示時に表示位置を決めるスロット
        void slot_popup_menu_position( int& x, int& y, bool& push_in );

        // ポップアップメニューがhideした時に呼び出されるスロット
        void slot_hide_popupmenu();

        // ポップアップメニューを表示する前にメニューのアクティブ状態を切り替える
        virtual void activate_act_before_popupmenu( const std::string& url ){}

        //  ポップアップメニュー取得
        virtual Gtk::Menu* get_popupmenu( const std::string& url ){ return NULL; }

    public:

        SIG_HIDE_POPUP sig_hide_popup(){ return m_sig_hide_popup; }
        SIG_RESIZE_POPUP sig_resize_popup(){ return m_sig_resize_popup; }
        
        View( const std::string& url, const std::string& arg1 = std::string(), const std::string& arg2 = std::string() );
        virtual ~View(){}

        virtual const std::string& get_url(){ return m_url; }
        void set_url( const std::string& url ){ m_url = url; }
        void update_host( const std::string& host );

        // ロック/アンロック
        const bool is_locked() const { return m_locked; }
        void lock(){ m_locked = true; }
        void unlock(){ m_locked = false; }

        // view 上にマウスポインタがあれば true
        bool is_mouse_on_view();

        // 各view個別のコマンド
        virtual bool set_command( const std::string& command, const std::string& arg = std::string() ){ return true; }

        // コピー用のURL
        virtual const std::string url_for_copy(){ return m_url; }

        // メインウィンドウのタイトルバーに表示する文字列
        virtual const std::string& get_title(){ return m_title; }

        // メインウィンドウのステータスバーに表示する文字列
        virtual const std::string& get_status(){ return m_status; }

        // クライアント領域の幅、高さ
        virtual const int width_client(){ return m_width_client; }
        virtual const int height_client(){ return m_height_client; }
        void set_width_client( int val ){ m_width_client = val; }
        void set_height_client( int val ){ m_height_client = val; }

        // オートリロード可能か
        const bool get_enable_autoreload() const { return m_enable_autoreload; }

        // オートリロードのモード設定
        void set_autoreload_mode( int mode, int sec );

        // 現在のオートリロードのモード取得
        const int get_autoreload_mode() const { return m_autoreload_mode; }

        // アイコンのID取得
        virtual const int get_icon( const std::string& iconname ){ return -1; }

        // ロード中
        virtual const bool is_loading(){ return false;}

        // 更新した
        virtual const bool is_updated(){ return false;}

        // 更新チェックして更新可能か
        virtual const bool is_check_update(){ return false;}

        // 古いデータか
        virtual const bool is_old(){ return false;}

        // 壊れているか
        virtual const bool is_broken(){ return false; }

        // shutdown( SIGHUP )用
        virtual void shutdown(){}

        // クロック入力
        // clock_in()はビューがアクティブのときに呼び出される
        // clock_in_always()はviewの種類に依らず常に呼び出されるので重い処理を含めてはいけない
        virtual void clock_in(){};
        virtual void clock_in_always();

        virtual void reload(){}
        virtual void stop(){}
        virtual void show_view(){}
        virtual void redraw_view(){}
        virtual void relayout(){}
        virtual void update_view(){}
        virtual void update_finish(){}        
        virtual void focus_view(){}
        virtual void focus_out(){ m_control.MG_reset(); }
        virtual void close_view(){}
        virtual void delete_view(){}
        virtual void update_item( const std::string& ){}
        virtual void operate_view( const int& ){}
        virtual void goto_top(){}
        virtual void goto_bottom(){}
        virtual void goto_num( int num ){}
        virtual void scroll_up(){}
        virtual void scroll_down(){}
        virtual void scroll_left(){}
        virtual void scroll_right(){}
        virtual void toggle_toolbar(){}
    };
}

#endif
