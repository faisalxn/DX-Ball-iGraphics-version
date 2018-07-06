#include "iGraphics.h" ;
#include <vector> ;
#include <iostream> ;

using namespace std ;

vector<bool>v;


const int NUMBER_OF_BRICKS  = 210 ;


int brick_lft,brick_btm,brick_dx,brick_dy;
int paddle_lft,paddle_btm,paddle_dx,paddle_dy;
int ball_x , ball_y ;
int dx = 5 , dy = 8 ;
int brick_counter ;
int score ;




bool start_of_the_game = true ;
bool starting_position_of_paddle = true ;
bool first_tym_print_of_brick = true ;
bool game_over_bmp = false ;
bool paused = false ;
bool startGame = false ;
bool start_again_from_pause = false ;
bool from_ending_all_bricks = false ;
bool credits = false ;
bool ball_felt = false ;




void initializeAll();
void set_co_ordinate();
void increase_brick_co_ordinate();
void increase_brick_co_ordinate_2nd();
void draw_paddle();
void set_paddle_co_ordinate();
void set_ball_co_ordinate();
void draw_ball();
void run_ball();
void show_bmp();
void draw_bricks();
void running_game();
void pausing_game();
void showMenu();
void showCredits();
bool ok_right();
bool ok_left();
bool cheq_overLap();





void initializeAll(){


    start_of_the_game = true ;
    starting_position_of_paddle = true ;
    first_tym_print_of_brick = true ;
    game_over_bmp = false ; /// _____________________________________________________
    paused = false ;
    startGame = false ;
    start_again_from_pause = false ;
    from_ending_all_bricks = false ;
    credits = false ;
    ball_felt = false ;



    v.clear();



    brick_lft=5;
    brick_btm=500 ;
    brick_dx=50 ;
    brick_dy = 20 ;



    paddle_lft=400 ;
    paddle_btm=10;
    paddle_dx=160;
    paddle_dy=10;




    ball_x = (paddle_lft + paddle_lft + paddle_dx )/2.0;
    ball_y = 40 ;
}




void showCredits(){
        if(credits){
                iShowBMP(20,150,"credits.bmp");
        }
}



void set_co_ordinate(){
    brick_counter = 1 ;
    brick_lft=5;
    brick_btm=500 ;
    brick_dx=50 ;
    brick_dy = 20 ;
    if(first_tym_print_of_brick){
        v.push_back( true) ;
    }
}





void increase_brick_co_ordinate(){
    brick_lft+=(5+50);
    if(first_tym_print_of_brick){
        v.push_back(true);
    }
}





void increase_brick_co_ordinate_2nd(){
    brick_lft = 5 ;
    brick_btm+=(5+20);
    if(first_tym_print_of_brick){
        v.push_back(true);
    }
}





void draw_paddle(){
    iSetColor(188,196,197);
    iFilledRectangle(paddle_lft,paddle_btm,paddle_dx,paddle_dy);

}




void set_paddle_co_ordinate(){
    paddle_lft=400 ;
    paddle_btm=10;
    paddle_dx=160;
    paddle_dy=10;
}






void set_ball_co_ordinate(){
    ball_x = (paddle_lft + paddle_lft + paddle_dx )/2.0;
    ball_y = 40 ;
}








void draw_ball(){
    iSetColor(82,73,243);
    if(start_of_the_game)
        set_ball_co_ordinate() , start_of_the_game = false ;
    iFilledCircle(ball_x ,ball_y ,20);
}







void run_ball(){
    if(ball_x<5 || ball_x>1150 )
        dx = - dx ;
    if( ball_y>800 )
        dy = - dy ;
    if( ball_y<0 )
        game_over_bmp = true , ball_felt = true , iPauseTimer(0) ; /// ______________________________________

    if(ball_x>=paddle_lft && ball_x<=paddle_lft+paddle_dx  && ball_y-20<=paddle_dy+paddle_btm && dy<0 )
        dy = -dy , ball_y = paddle_btm + paddle_dy + 20  ;
    ball_x+=dx;
    ball_y+=dy;
}




void show_bmp(){
    ///game over
    iShowBMP(50,150,"over.bmp");
    char s[100] ;
    sprintf(s,"Press M For Going To Menu");
    iText(430,100,s,GLUT_BITMAP_TIMES_ROMAN_24);

}




void draw_bricks(){
    iFilledRectangle(brick_lft,brick_btm,brick_dx,brick_dy);
}




bool cheq_overLap(){
    if(ball_x>=brick_lft && ball_x<=brick_lft+brick_dx && ball_y>=brick_btm && ball_y<=brick_btm+brick_dy)
        return true;
    else return false ;
}



void running_game(){
        char score_str[100] ;
        char pause_show[100];
        sprintf(pause_show,"Press P For Pause The Game");
        iText(10,765,pause_show,GLUT_BITMAP_TIMES_ROMAN_24);
    set_co_ordinate();
    bool f = true ;
        int i ;
        for(i = 1 ; i<=NUMBER_OF_BRICKS ; i++){
                if(f)iSetColor(219,78,36) , f = false ;
                else if(!f)iSetColor(128,221,34) , f = true ;
        if( cheq_overLap() && v[i-1] ){
                //brick_lft+=(10+50+50); // fixed by anindya
                v[i-1] = false ;
                dy = -dy ;
        }
        else if(v[i-1])
            draw_bricks();
        if( i%21!=0  )
            increase_brick_co_ordinate(); /// in same layer

        else {
            increase_brick_co_ordinate_2nd(); /// in different layer

        }
        }
        first_tym_print_of_brick = false ;
        if(starting_position_of_paddle)
        set_paddle_co_ordinate() , starting_position_of_paddle = false ;
        draw_paddle();
        draw_ball();
        iSetColor(255,255,255);
        score = 0 ;
        for(i = 0 ; i<v.size() ; i++)
                if(v[i]==false)
                        ++score ;
        sprintf(score_str,"Your Score is : %d",score);
        iText(940,765 , score_str ,GLUT_BITMAP_TIMES_ROMAN_24 ) ;
}





void pausing_game(){
    iShowBMP(50,150,"paused.bmp");
}





void showMenu(){
    iShowBMP(20,150,"menu.bmp");
}




void iDraw(){
        iClear();
        if(score==NUMBER_OF_BRICKS){
                game_over_bmp = true ; /// ______________________________________________
                iPauseTimer(0);
                from_ending_all_bricks = true ;
        }
        if(credits)
        showCredits();
        else if(!startGame)
                showMenu();
        else if(startGame){
            if(ball_felt)
                iResumeTimer(0) , ball_felt = false ;
            if(score!=0)
                iResumeTimer(0) , score = 0 ;
            if(paused){
                iPauseTimer(0);
                pausing_game();
            }
            else{
                if(game_over_bmp==false) /// _______________________________________________
                    running_game();
                else show_bmp();
            }
        }
}




/*
        function iMouseMove() is called when the user presses and drags the mouse.
        (mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my){
        //place your codes here
}




/*
        function iMouse() is called when the user presses/releases the mouse.
        (mx, my) is the position where the mouse pointer is.
*/




void iMouse(int button, int state, int mx, int my)
{
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(startGame==false){
            if(mx>=400 && mx<=764 && my>=428 && my<=493 && start_again_from_pause){
                initializeAll();
                startGame = true ;
                iResumeTimer(0);
                start_again_from_pause = false ;

            }
            else if(mx>=400 && mx<=764 && my>=428 && my<=493){
                initializeAll();
                startGame = true ;
            }
            if(mx>=400 && mx<=764 && my>=173 && my<=237){
                exit(0);
            }
            printf("%d %d\n",mx,my);
            if(mx>=400 && mx<=764 && my>=258 && my<=321){
                credits = true ;
                //showCredits();
            }
            }
                if(paused){

                        if(mx>=380 && mx<=680 && my>=388 && my<=470){
                                paused = false ;
                                iResumeTimer(0);
                        }
                        if(mx>=435 && mx<=635 && my>=273 && my<=345){
                                startGame = false ;
                                initializeAll();
                                start_again_from_pause = true ;
                        }
                }
        }
        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){

        }
}



/*
        function iKeyboard() is called whenever the user hits a key in keyboard.
        key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key){
        if(credits){
        if(key == '\b'){
            //cout<<"backspace"<<endl;
            credits = false ;

        }
        }
    if((key=='p' || key=='P' ) && ball_felt==false )
        paused = true  ;
    if((key=='r' || key=='R') && paused==true )
        paused = false  , iResumeTimer(0);
        if(game_over_bmp ){ /// _______________________________________________________
                if(key=='m' || key=='M' ){
                        startGame = false ;
                        initializeAll();
                        game_over_bmp = false ;  /// ____________________________________
                }
        }
}





bool ok_right(){
    return ((paddle_lft+paddle_dx+50<=1160) ? true : false )  ;
}






bool ok_left(){
    return ((paddle_lft-50>=0) ? true : false )  ;
}



/*
        function iSpecialKeyboard() is called whenver user hits special keys like-
        function keys, home, end, pg up, pg down, arraows etc. you have to use
        appropriate constants to detect them. A list is:
        GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
        GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
        GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
        GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/




void iSpecialKeyboard(unsigned char key){

        if(key == GLUT_KEY_END){
                exit(0);
        }
        if(key == GLUT_KEY_RIGHT){
        if(ok_right())
            paddle_lft+=50 ;
        }
        if(key == GLUT_KEY_LEFT){
        if(ok_left())
            paddle_lft-=50 ;
        }


        //place your codes for other keys here
}


int main(){
        //place your own initialization codes here.
    iSetTimer(15,run_ball);
        iInitialize( 1160 , 800 ,"DX-BALL" ) ; /// length = 1160    hieght = 800
        return 0;
}
