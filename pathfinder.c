#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 987654321

int dijkDist[100][100];
int dijkSteps[100][100];
int dijkVisited[100][100];

int bfsDist[100][100];
int bfsVisited[100][100];

int map[100][100];
int dijkmap[100][100];
int BFSmap[100][100];

int dijkparentx[100][100];
int dijkparenty[100][100];

int bfsparentx[100][100];
int bfsparenty[100][100];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

struct queue
{
    int queue[1000];
    int front;
    int back;
};
struct queue qx, qy;

void q_init(struct queue *q)
{
    q->front = 0;
    q->back = 0;
}

void q_push(struct queue *q, int x)
{
    q->queue[q->back++] = x;
}

int q_pop(struct queue *q)
{
    return q->queue[q->front++];
}

int q_empty(struct queue *q)
{
    return q->front == q->back;
}

void pop_min(struct queue *qx, struct queue *qy, int *x, int *y)
{
    int min_idx = qx->front;
    int min_cost = dijkDist[qx->queue[min_idx]][qy->queue[min_idx]];

    for (int i = qx->front; i < qx->back; i++)
    {
        int cx = qx->queue[i];
        int cy = qy->queue[i];

        if (dijkDist[cx][cy] < min_cost)
        {
            min_cost = dijkDist[cx][cy];
            min_idx = i;
        }
    }

    *x = qx->queue[min_idx];
    *y = qy->queue[min_idx];

    // min_idx 위치를 마지막 원소로 덮어서 삭제
    qx->queue[min_idx] = qx->queue[qx->back - 1];
    qy->queue[min_idx] = qy->queue[qy->back - 1];

    qx->back--;
    qy->back--;
}
void input_map()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            scanf("%d", &map[i][j]);
            dijkVisited[i][j] = 0;
            dijkDist[i][j] = INF;
            dijkSteps[i][j] = INF;
        }
    }
}
void dijkstra()
{
    struct queue qx, qy;
    q_init(&qx);
    q_init(&qy);

    if (map[0][0] == 0 || map[9][9] == 0)
    {
        return;
    }
    int x;
    int y;

    dijkDist[0][0] = 0;
    dijkSteps[0][0] = 0;

    q_push(&qx, 0);
    q_push(&qy, 0);

    while (q_empty(&qx) == 0)
    {
        pop_min(&qx, &qy, &x, &y);

        if (dijkVisited[x][y] == 1)
            continue;

        dijkVisited[x][y] = 1;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dr[i];
            int ny = y + dc[i];

            if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10)
                continue;

            if (dijkVisited[nx][ny] == 1)
                continue;

            if (map[nx][ny] == 0)
                continue;

            int cost = dijkDist[x][y] + map[nx][ny];

            if (dijkDist[nx][ny] > cost)
            {
                dijkDist[nx][ny] = cost;
                dijkSteps[nx][ny] = dijkSteps[x][y] + 1;

                dijkparentx[nx][ny] = x;
                dijkparenty[nx][ny] = y;

                q_push(&qx, nx);
                q_push(&qy, ny);
            }
        }
    }
}
void init_diarrays()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            dijkDist[i][j] = INF;
            dijkSteps[i][j] = INF;
        }
    }
}
void rev_dijk(int x, int y)
{

    while (!(x == 0 && y == 0))
    {
        if (!(x == 9 && y == 9))
            dijkmap[x][y] = -2;

        int px = dijkparentx[x][y];
        int py = dijkparenty[x][y];

        x = px;
        y = py;
    }
    dijkmap[0][0] = -3;
    dijkmap[9][9] = -4;
}

void rev_bfs(int x,int y){
    while (!(x == 0 && y == 0))
    {
        if (!(x == 9 && y == 9))
            BFSmap[x][y] = -2;

        int px = bfsparentx[x][y];
        int py = bfsparenty[x][y];

        x = px;
        y = py;
    }
    BFSmap[0][0] = -3;
    BFSmap[9][9] = -4;
}
void result_dijk()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            dijkmap[i][j] = map[i][j];
        }
    }

    if (dijkDist[9][9] == INF)
    {
        printf("도착 불가능\n");
        return;
    }
    else
    {
        printf("최소 비용: %d\n", dijkDist[9][9]);
        printf("이동 거리: %d\n", dijkSteps[9][9]);
    }
    rev_dijk(9, 9);
    printf("\n다익스트라 지도\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (dijkmap[i][j] == -3)
                printf("S ");
            else if (dijkmap[i][j] == -4)
                printf("G ");
            else if (dijkmap[i][j] == -2)
                printf("* ");
            else
                printf("%d ", dijkmap[i][j]);
        }
        printf("\n");
    }
}
void result_bfs()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)        
        {
            BFSmap[i][j] = map[i][j];
        }
    }
    if (bfsDist[9][9] == INF)
    {
        printf("도착 불가능\n");
        return;
    }
    else
    {
        printf("최단 이동 거리: %d\n", bfsDist[9][9]);
    }
    rev_bfs(9,9);
    printf("\nBFS 지도\n");

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (BFSmap[i][j] == -3)
                printf("S ");
            else if (BFSmap[i][j] == -4)
                printf("G ");
            else if (BFSmap[i][j] == -2)
                printf("* ");
            else
                printf("%d ", BFSmap[i][j]);
        }
        printf("\n");
    }
}
void init_bfsarray()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            bfsDist[i][j] = INF;
            bfsVisited[i][j] = 0;
        }
    }
}
void BFS()
{
    struct queue qx, qy;
    q_init(&qx);
    q_init(&qy);

    if (map[0][0] == 0 || map[9][9] == 0)
        return;

    q_push(&qx, 0);
    q_push(&qy, 0);

    bfsDist[0][0] = 0;
    bfsVisited[0][0] = 1;
    while (q_empty(&qx) == 0)
    {
        int x = q_pop(&qx);
        int y = q_pop(&qy);
        for (int i = 0; i < 4; i++)
        {
            
            int nx = x + dr[i];
            int ny = y + dc[i];

            if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10)
                continue;

            if (map[nx][ny] == 0)
                continue;

            if (bfsVisited[nx][ny] == 1)
                continue;

            bfsVisited[nx][ny] = 1;
            bfsDist[nx][ny] = bfsDist[x][y] + 1;

            bfsparentx[nx][ny] = x;
            bfsparenty[nx][ny] = y;

            q_push(&qx, nx);
            q_push(&qy, ny);
        }
    }
}
int main()
{

    input_map();

    init_diarrays();
    init_bfsarray();

    dijkstra();
    BFS();

    result_dijk();
    result_bfs();
}
