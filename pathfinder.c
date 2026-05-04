#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 987654321

int visited[100][100];
int dist[100][100];
int map[100][100];
int copymap[100][100];
int steps[100][100];
int parentx[100][100];
int parenty[100][100];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

struct queue
{
    int queue[1000];
    int front;
    int back;
};
struct queue qx;
struct queue qy;

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
    int min_cost = dist[qx->queue[min_idx]][qy->queue[min_idx]];

    for (int i = qx->front; i < qx->back; i++)
    {
        int cx = qx->queue[i];
        int cy = qy->queue[i];

        if (dist[cx][cy] < min_cost)
        {
            min_cost = dist[cx][cy];
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
            visited[i][j] = 0;
            dist[i][j] = INF;
            steps[i][j] = INF;
        }
    }
}
void dijkstra()
{
    if (map[0][0] == 0 || map[9][9] == 0)
    {
        return;
    }
    q_init(&qx);
    q_init(&qy);

    int x;
    int y;

    dist[0][0] = 0;
    steps[0][0] = 0;

    q_push(&qx, 0);
    q_push(&qy, 0);

    while (q_empty(&qx) == 0)
    {
        pop_min(&qx, &qy, &x, &y);

        if (visited[x][y] == 1)
            continue;

        visited[x][y] = 1;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dr[i];
            int ny = y + dc[i];

            if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10)
                continue;

            if (visited[nx][ny] == 1)
                continue;

            if (map[nx][ny] == 0)
                continue;

            int cost = dist[x][y] + map[nx][ny];

            if (dist[nx][ny] > cost)
            {
                dist[nx][ny] = cost;
                steps[nx][ny] = steps[x][y] + 1;

                parentx[nx][ny] = x;
                parenty[nx][ny] = y;

                q_push(&qx, nx);
                q_push(&qy, ny);
            }
        }
    }
}
void init_arrays()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            dist[i][j] = INF;
            steps[i][j] = INF;
        }
    }
}
void rev(int x, int y)
{

    while (!(x == 0 && y == 0))
    {
        if (!(x == 9 && y == 9))
            copymap[x][y] = -2;

        int px = parentx[x][y];
        int py = parenty[x][y];

        x = px;
        y = py;
    }
    copymap[0][0] = -3;
    copymap[9][9] = -4;
}
void result()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            copymap[i][j] = map[i][j];
        }
    }

    if (dist[9][9] == INF)
    {
        printf("도착 불가능\n");
        return;
    }
    else
    {
        printf("최소 비용: %d\n", dist[9][9]);
        printf("이동 거리: %d\n", steps[9][9]);
    }
    rev(9, 9);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (copymap[i][j] == -3)
                printf("S ");
            else if (copymap[i][j] == -4)
                printf("G ");
            else if (copymap[i][j] == -2)
                printf("* ");
            else
                printf("%d ", copymap[i][j]);
        }
        printf("\n");
    }
}

int main()
{

    input_map();

    init_arrays();

    dijkstra();

    result();
}
