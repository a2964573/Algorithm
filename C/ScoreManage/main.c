#include <stdio.h>
#include <string.h>

#define TRUE                 1
#define FALSE                0

#define SERVICE_SCORE_INPUT  1
#define SERVICE_SCORE_OUTPUT 2
#define SERVICE_RANK_OUTPUT  3

#define TERM_FIRST           1
#define TERM_SECOND          2

#define SUBJECT_KOREAN       1
#define SUBJECT_ENGLISH      2
#define SUBJECT_MATH         3

typedef struct _INFO {
    char         name     [32];
    char         subject  [32];
    unsigned int score;
    unsigned int term;
} INFO;

int input_score_func(INFO* outInfo)
{
    char         name     [32];
    char         subject  [32];
    unsigned int score     = 0;
    unsigned int term      = 0;
    int          sub_flag  = 0;
    int          len       = 0;

    while(TRUE) {
        printf("�б⸦ �Է��ϼ���\n");
        printf("1: 1�б�, 2: 2�б�\n\n");
        scanf("%d", &term);
        printf("\n");

        if(term < 1 && term > 2) {
            printf("�߸��� ���� �Է��Ͽ����ϴ�.\n\n");
            continue;
        }

        printf("%d�б� ������ �Է��մϴ�..\n", term);
        printf("�̸��� �Է��ϼ���.\n\n");
        scanf("%s", &name);
        printf("\n");

        len = strlen(name);
        name[len] = 0x00;

        printf("�Է��� �̸��� \'%s\'�Դϴ�.\n\n", name);

        printf("������ �Է����ּ���.\n");
        printf("1: ����, 2: ����, 3: ����\n\n");
        scanf("%d", &sub_flag);
        printf("\n");

        switch(sub_flag) {
            case SUBJECT_KOREAN :
                len = sprintf(subject, "����");
            break;
            case SUBJECT_ENGLISH:
                len = sprintf(subject, "����");
            break;
            case SUBJECT_MATH   :
                len = sprintf(subject, "����");
            break;
            default:
                len = 0;
            break;
        }

        subject[len] = 0x00;

        if(subject[0] == 0x00) {
            printf("�߸��� ���� �Է��Ͽ����ϴ�.\n\n");
            continue;
        }

        printf("%s ������ �Է����ּ���.\n", subject);
        printf("0 ~ 100\n\n");
        scanf("%d", &score);
        printf("\n");

        if(score < 0 || score > 100) {
            printf("�߸��� ���� �Է��Ͽ����ϴ�.\n\n");
            continue;
        }

        printf("%d�б� %s���� %s���� ������ %d�� �Դϴ�.\n\n"
            , term, name, subject, score);

        break;
    }

    strcpy(outInfo->name,    name);
    strcpy(outInfo->subject, subject);
    outInfo->score = score;
    outInfo->term  = term;

    return 0;
}

void main(int argc, char** argv)
{
    char mode_name[64] = {0,}; // 1: �����Է�, 2: �������, 3: ��ŷ���
    int  mode          = 0;    // 1: �����Է�, 2: �������, 3: ��ŷ���
    int  term          = 0;    // 1: 1�б�, 2: 2�б�
    int  rtn           = 0;

    printf("#############################\n");
    printf("#                           #\n");
    printf("#  �������� ���α׷��Դϴ�  #\n");
    printf("#                           #\n");
    printf("#############################\n\n");

    while(TRUE) {
        printf("������ ���񽺸� �Է����ּ���.\n");
        printf("1: �����Է�, 2: �������, 3: ��ŷ���\n\n");
        scanf("%d", &mode);
        printf("\n");

        switch(mode) {
            case SERVICE_SCORE_INPUT :
                strcpy(mode_name, "�����Է�");
            break;
            case SERVICE_SCORE_OUTPUT:
                strcpy(mode_name, "�������");
            break;
            case SERVICE_RANK_OUTPUT :
                strcpy(mode_name, "��ŷ���");
            break;
            default:
                mode_name[0] = 0x00;
            break;
        }

        if(mode_name[0] == 0x00) {
            printf("�߸��� ���񽺸� �Է��Ͽ����ϴ�.\n");
            printf("�ٽ� �Է����ּ���.\n\n");
            continue;
        }

        printf("%s���񽺸� �����մϴ�.\n\n", mode_name);
        break;
    }

    INFO info;
    memset(&info, 0, sizeof(INFO));

    switch(mode) {
        case SERVICE_SCORE_INPUT :
            rtn = input_score_func(&info);
            if(rtn == 0) {
                printf("> info->name    [%s]\n", info.name);
                printf("> info->subject [%s]\n", info.subject);
                printf("> info->score   [%d]\n", info.score);
                printf("> info->term    [%d]\n", info.term);
            }
        break;
        case SERVICE_SCORE_OUTPUT:
        break;
        case SERVICE_RANK_OUTPUT :
        break;
    }

    return;
}