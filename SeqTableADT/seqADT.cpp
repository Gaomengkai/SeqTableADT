#include "seqADT.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

#define _CRT_SECURE_NO_WARNINGS

status InitList(SqList& L) {
    /// <summary>
    /// 1. ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
    /// </summary>
    /// <param name="L">Ҫ��������Ա�</param>
    /// <returns>OK/INFEASIBLE/ERROR</returns>
    if (L.elem != NULL)return INFEASIBLE;
    L.elem = (ElemType*)calloc(LIST_INIT_SIZE, sizeof(ElemType));
    if (L.elem == NULL)return ERROR; // Memory allocation error
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}


status DestroyList(SqList& L) {
    /// <summary>
    /// 2. ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
    /// </summary>
    /// <param name="L">Ҫ���ٵ����Ա�</param>
    /// <returns>״̬��</returns>
    if (L.elem == NULL) return INFEASIBLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}


status ClearList(SqList& L) {
    /// <summary>
    /// 3. ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
    /// </summary>
    /// <param name="L">Ҫ��������Ա�</param>
    /// <returns>״̬��</returns>
    if (!L.elem) return INFEASIBLE;
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L) {
    /// <summary>
    /// 4. ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��
    /// ������Ա�L�����ڣ�����INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    if (L.length) return FALSE;
    return TRUE;
}
int ListLength(SqList L) {
    /// <summary>
    /// 5. ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    return L.length;
}
status GetElem(SqList L, int i, ElemType& e)
{
    /// <summary>
    /// 6. ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK��
    /// ���i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    /// </summary>
    /// <param name="L">Ҫ���������Ա�</param>
    /// <param name="i"></param>
    /// <param name="e"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    if (i > L.length || i <= 0) return ERROR;
    e = L.elem[i - 1];
    return OK;
}
int LocateElem(SqList L, ElemType e) {
    /// <summary>
    /// 7. ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų�����OK��
    /// ���e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <param name="e"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) return i + 1;
    }
    return ERROR;
}
status PriorElem(SqList L, ElemType e, ElemType& pre) {
    /// <summary>
    /// 8. ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK��
    /// ���û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <param name="e"></param>
    /// <param name="pre"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    if (*L.elem == e) return ERROR;
    for (int i = 1; i < L.length; ++i) {
        if (L.elem[i] == e) {
            pre = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR;
}
status NextElem(SqList L, ElemType e, ElemType& next) {
    /// <summary>
    /// 9. ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK��
    /// ���û�к�̣�����ERROR��
    /// ������Ա�L�����ڣ�����INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <param name="e"></param>
    /// <param name="next"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    if (L.elem[L.length - 1] == e) return ERROR;
    for (int i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == e) {
            next = L.elem[i + 1];
            return OK;
        }
    }
    return ERROR;
}

// rewrite ListInsert
status ListInsert(SqList& L, int i, ElemType e) {
    /// <summary>
    /// 10. ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ
    /// ����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    /// </summary>14
    /// <param name="L"></param>
    /// <param name="i"></param>
    /// <param name="e"></param>
    /// <returns></returns>

    if (!L.elem) return INFEASIBLE;
    if (i < 1 || i > L.length + 1) return ERROR;
    --i;
    // To locate the logic number of i.
    // i th element's index is i-1
    if (L.length == L.listsize) {
        // realloc memory to store more data (such as e)
        ElemType* t = (ElemType*)realloc(L.elem, sizeof(ElemType) * ((size_t)L.length + LISTINCREMENT));
        L.elem = t;
        if (L.elem == NULL)return ERROR;
        L.listsize += LISTINCREMENT;
    }
    for (int j = L.length - 1; j >= i; --j) {
        memcpy(L.elem + j + 1, L.elem + j, sizeof(ElemType));
    }
    memcpy(L.elem + i, &e, sizeof(ElemType));
    ++L.length;
    return OK;
}

status ListDelete(SqList& L, int i, ElemType& e) {
    /// <summary>
    /// 11. ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK��
    /// ��ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <param name="i"></param>
    /// <param name="e"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    if (i > L.length || i < 1) return ERROR;
    e = L.elem[i - 1];
    for (int j = i - 1; j < L.length - 1; j++) {
        L.elem[j] = L.elem[j + 1];
    }
    L.length -= 1;
    return OK;
}
status ListTraverse(SqList L) {
    /// <summary>
    /// 12. ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�
    /// ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    for (int i = 0; i < L.length - 1; i++) {
        printf("%d ", L.elem[i]);
    }
    if (L.length != 0) printf("%d", L.elem[L.length - 1]);
    return OK;
}
status SaveList(SqList L, char FileName[]) {
    /// <summary>
    /// 13. ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�
    /// ����OK�����򷵻�INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <param name="FileName"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    FILE* fp = fopen(FileName, "w");
    if (fp == NULL) return FILEERROR;
    fwrite(&L.length, sizeof(ElemType), 1, fp);
    fwrite(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    return OK;
}
status LoadList(SqList& L, char FileName[]) {
    /// <summary>
    /// 14. ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�
    /// ����OK�����򷵻�INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <param name="FileName"></param>
    /// <returns></returns>
    if (L.elem) return INFEASIBLE;
    int cnt = 0;
    FILE* fp = fopen(FileName, "r");
    if (fp == NULL) return FILEERROR;
    fread(&L.length, sizeof(ElemType), 1, fp);
    if (L.length <= 0)return ERROR;
    L.elem = (ElemType*)calloc((size_t)L.length * 2, sizeof(ElemType));
    if (L.elem == NULL)return ERROR;
    L.listsize = L.length * 2;
    fread(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    return OK;
}

status AddList(LISTS& Lists, char ListName[]) {
    /// <summary>
    /// 15. ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա�
    /// ���Ա������ֺ�̨���Գ�����롣
    /// 
    /// </summary>
    /// <param name="Lists"></param>
    /// <param name="ListName"></param>
    /// <returns></returns>
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.elem = (ElemType*)calloc(LIST_INIT_SIZE, sizeof(ElemType));
    if (Lists.elem[Lists.length].L.elem == NULL) return ERROR;
    Lists.length += 1;
    return OK;
}

status RemoveList(LISTS& Lists, char ListName[]) {
    /// <summary>
    /// 16. �Ƴ�һ������ΪListName�����Ա�
    /// </summary>
    /// <param name="Lists"></param>
    /// <param name="ListName"></param>
    /// <returns></returns>
    for (int i = 0; i < Lists.length; ++i) {
        if (!strcmp(Lists.elem[i].name, ListName)) {
            for (int j = i + 1; j < Lists.length; ++j) {
                Lists.elem[j - 1] = Lists.elem[j];
            }
            Lists.length -= 1;
            return OK;
        }
    }
    return ERROR;
}

int LocateList(LISTS Lists, char ListName[]) {
    /// <summary>
    /// 17. ��Lists�в���һ�����Ա�
    /// </summary>
    /// <param name="Lists"></param>
    /// <param name="ListName"></param>
    /// <returns></returns>
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            return i + 1;
        }
    }
    return ERROR;
}