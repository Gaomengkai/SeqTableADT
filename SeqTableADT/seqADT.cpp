#include "seqADT.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

#define _CRT_SECURE_NO_WARNINGS

status InitList(SqList& L) {
    /// <summary>
    /// 1. 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
    /// </summary>
    /// <param name="L">要构造的线性表</param>
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
    /// 2. 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
    /// </summary>
    /// <param name="L">要销毁的线性表</param>
    /// <returns>状态码</returns>
    if (L.elem == NULL) return INFEASIBLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}


status ClearList(SqList& L) {
    /// <summary>
    /// 3. 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
    /// </summary>
    /// <param name="L">要清除的线性表</param>
    /// <returns>状态码</returns>
    if (!L.elem) return INFEASIBLE;
    L.length = 0;
    return OK;
}

status ListEmpty(SqList L) {
    /// <summary>
    /// 4. 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；
    /// 如果线性表L不存在，返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    if (L.length) return FALSE;
    return TRUE;
}
int ListLength(SqList L) {
    /// <summary>
    /// 5. 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (!L.elem) return INFEASIBLE;
    return L.length;
}
status GetElem(SqList L, int i, ElemType& e)
{
    /// <summary>
    /// 6. 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；
    /// 如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /// </summary>
    /// <param name="L">要操作的线性表</param>
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
    /// 7. 如果线性表L存在，查找元素e在线性表L中的位置序号并返回OK；
    /// 如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
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
    /// 8. 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；
    /// 如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
    /// 9. 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；
    /// 如果没有后继，返回ERROR；
    /// 如果线性表L不存在，返回INFEASIBLE。
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
    /// 10. 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时
    /// 返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
    /// 11. 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；
    /// 当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
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
    /// 12. 如果线性表L存在，依次显示线性表中的元素，
    /// 每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
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
    /// 13. 如果线性表L存在，将线性表L的的元素写到FileName文件中，
    /// 返回OK，否则返回INFEASIBLE。
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
    /// 14. 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，
    /// 返回OK，否则返回INFEASIBLE。
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
    /// 15. 只需要在Lists中增加一个名称为ListName的空线性表，
    /// 线性表数据又后台测试程序插入。
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
    /// 16. 移除一个名字为ListName的线性表
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
    /// 17. 在Lists中查找一个线性表
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