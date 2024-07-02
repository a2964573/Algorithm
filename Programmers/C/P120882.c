// ���� ������ ���� ������ ��� ������ �������� �л����� ����� �ű���� �մϴ�. 
// ���� ������ ���� ������ ���� 2���� ���� �迭 score�� �־��� ��, 
// ���� ������ ���� ������ ����� �������� �ű� ����� ���� �迭�� return�ϵ��� solution �Լ��� �ϼ����ּ���.

#include <stdio.h>

// score_rows�� 2���� �迭 score�� �� ����, score_cols�� 2���� �迭 score�� �� �����Դϴ�.
int* solution(int** score, size_t score_rows, size_t score_cols)
{
    // return ���� malloc �� ���� �Ҵ��� ������ּ���. �Ҵ� ���̴� ��Ȳ�� �°� �������ּ���.
    int* answer = (int*)malloc(sizeof(int) * score_rows);
    memset(answer, 0x00, sizeof(int) * score_rows);

    int sumA;
    int sumB;
    int aPos;
    int bPos;
    for(aPos = 0; aPos < score_rows; aPos++){
        answer[aPos]++;
        sumA = score[aPos][0] + score[aPos][1];

        for(bPos = 0; bPos < score_rows; bPos++){
            if(aPos == bPos){
                continue;
            }

            sumB = score[bPos][0] + score[bPos][1];

            if(sumA < sumB){
                answer[aPos]++;
            }
        }
    }

    return answer;
}