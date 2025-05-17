#include<iostream>
#include<easyx.h>/*图形库*/
using namespace std;
IMAGE tree1;/*引用图片*/
#define kuan 25/*设置格子之间的宽度*/
#define jiange 75/*设置左边的运行框到最左边轴的距离*/
#define row 19
#define col 19
int map[row][col];
void draw();
bool gameover = false;
enum chess
{
	node,black,white
};
struct
{
	int x;
	int y;
	int row1;
	int col1;
	bool add ;
	chess chessplayer;
}point={0,0,0,0,false,black};
bool winorlose(int row1,int col1)
{
    const int directions[4][2] = {
        {0, 1},    // 水平方向
        {1, 0},    // 垂直方向
        {1, 1},    // 右斜方向
        {1, -1}    // 左斜方向
    };

    // 遍历四个方向
    for (int d = 0; d < 4; d++)
    {
        int count = 1;  // 当前方向的连续棋子数
        
        // 向正方向查找
        for (int i = 1; i < 5; i++)
        {
            int newRow = row1 + directions[d][0] * i;
            int newCol = col1 + directions[d][1] * i;
            
            if (newRow < 0 || newRow >= 19 || newCol < 0 || newCol >= 19 || 
                map[newRow][newCol] != point.chessplayer)//防止溢出边界
            {
                break;
            }
            count++;
        }
        
        // 向反方向查找
        for (int i = 1; i < 5; i++)
        {
            int newRow = row1 - directions[d][0] * i;
            int newCol = col1 - directions[d][1] * i;
            
            if (newRow < 0 || newRow >= 19 || newCol < 0 || newCol >= 19 || 
                map[newRow][newCol] != point.chessplayer)//防止溢出边界
            {
                break;
            }
            count++;
        }
        
        // 如果任何方向达到5个连续棋子，则获胜
        if (count >= 5)
        {
            return true;
        }
    }
    return false;
}
void mousemove()
{
	if (gameover)
	{
		return;
	}
	ExMessage pp;
	if (peekmessage(&pp))
	{
		point.add = false;
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				int gx = (j + 3) * kuan;
				int gy = (i + 3) * kuan;
				if (abs(pp.x - gx) < 12 && abs(pp.y - gy) < 12)
				{
					point.x = gx;
					point.y = gy; 
					point.col1 = i;
					point.row1 = j;
					point.add = true;
					break;
				}
			}
			if (point.add)break;
		}
		if (pp.message == WM_LBUTTONDOWN && map[point.col1][point.row1] == node)
		{
			map[point.col1][point.row1] = point.chessplayer;
			if (winorlose(point.col1, point.row1))
				{

				draw();
				FlushBatchDraw();
			if (point.chessplayer == black)
				{
				MessageBox(GetHWnd(), L"胜利！", L"祝贺你，黑方！", MB_OK);
				}
				else
				{
				MessageBox(GetHWnd(), L"胜利！", L"祝贺你，白方！", MB_OK);
				}
								gameover = true;
								
			}
	point.chessplayer = (point.chessplayer == black ? white : black);//切换棋手，比如在黑方下完就轮到红方了
							//如果棋手等于黑，就先下，若不等于就让红方下
	  }		
	}
}
void draw()
{
	setlinecolor(BLACK);/*设置颜色为黑色*/
	setlinestyle(PS_SOLID,3);/*设置画笔样式*/
	for (int i = 0; i < 19; i++)
	{
		line(jiange, jiange + kuan * i, jiange + kuan * 18, jiange + kuan * i);/*绘画横线，x变，y不变，x从小变到大*/
		line(jiange + kuan * i, jiange, jiange + kuan * i, jiange + kuan * 18);/*绘画竖线，y变，x不变，y从小变到大*/
	}
	setfillcolor(RED);/*在指定位置画五个点,颜色为红色*/
	solidcircle(175,175,7);/*第一个参数代表x轴，第二个代表y轴，第三个代表圆的半径，计算坐标时，一定要从75开始算，因为运行框到棋盘的边框间隔是75*/
	solidcircle(425, 175, 7);/*计算x的坐标时，要从最上面的棋盘边轴开始，也就是75*/
	solidcircle(175, 375, 7);/*计算y的坐标时，一定要从最左边的棋盘边轴开始*/
	solidcircle(425, 375, 7);/*7为圆的半径*/
	solidcircle(300, 300, 7);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			switch(map[i][j])
			{
			case node:break;
			case black:setfillcolor(BLACK);
				solidcircle(j * kuan + jiange, i * kuan + jiange, 8); break;
			case white:setfillcolor(WHITE);
				solidcircle(j * kuan + jiange, i * kuan + jiange, 8); break;
			default:break;
			}
		}
		
	}
	
}
int main()
{
	initgraph(600, 540);/*600为左右两边的宽，540为上下两边的高*/
	loadimage(&tree1, L"E:\\VS2022\\五子棋项目\\images\\tree1.jpg");/*加载图片*/
	putimage(0, 0, &tree1);/*输出图片*/
	BeginBatchDraw();/*双缓冲技术，开始创建画布*/
	while (1)
	{
		cleardevice();/*清屏*/
		putimage(0, 0, &tree1);/*通过循环不断的清屏和输出图片，能保证图片的帧率，让画质更细腻*/
		draw();/*不断的绘制线条*/
		mousemove();
		FlushBatchDraw();/*不断绘画*/
	}
	EndBatchDraw();/*结束绘画*/
	cin.get();/*防止程序一闪退出*/


}