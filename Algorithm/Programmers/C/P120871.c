// 3x ���� ������� 3�� ������ ���ڶ�� �����ϱ� ������ 3�� ����� ���� 3�� ������� �ʽ��ϴ�. 
// ���� n�� �Ű������� �־��� ��, 
// n�� 3x �������� ����ϴ� ���ڷ� �ٲ� return�ϵ��� solution �Լ��� �ϼ����ּ���.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int find_three(int n)
{
    char number[16] = {0,};
    int len = sprintf(number, "%d", n);

    int pos;
    for(pos = 0; pos < len; pos++){
        if(number[pos] == '3'){
            return 1;
        }
    }

    return 0;
}

int solution(int n) {
    int answer = n;

    int pos;
    for(pos = 1; pos <= answer; pos++){
        if(find_three(pos) == 1){
            answer++;
            continue;
        }

        if(pos % 3 == 0){
            answer++;
            continue;
        }
    }

    return answer;
}