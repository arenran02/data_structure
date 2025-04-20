#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int coeff;  // 계수
    int exp;    // 지수
    struct Term* next;
} Term;

// 새 항 생성
Term* createTerm(int coeff, int exp) {
    Term* newTerm = (Term*)malloc(sizeof(Term));
    newTerm->coeff = coeff;
    newTerm->exp = exp;
    newTerm->next = NULL;
    return newTerm;
}

// 항을 다항식에 삽입 (지수 내림차순 정렬)
void insertTerm(Term** poly, int coeff, int exp) {
    if (coeff == 0) return;

    Term* newTerm = createTerm(coeff, exp);
    if (*poly == NULL || (*poly)->exp < exp) {
        newTerm->next = *poly;
        *poly = newTerm;
    } else {
        Term* curr = *poly;
        Term* prev = NULL;
        while (curr != NULL && curr->exp > exp) {
            prev = curr;
            curr = curr->next;
        }
        if (curr != NULL && curr->exp == exp) {
            curr->coeff += coeff;
            free(newTerm);
            if (curr->coeff == 0) {
                if (prev == NULL) *poly = curr->next;
                else prev->next = curr->next;
                free(curr);
            }
        } else {
            newTerm->next = curr;
            if (prev) prev->next = newTerm;
            else *poly = newTerm;
        }
    }
}

// 다항식 출력
void printPoly(Term* poly) {
    while (poly != NULL) {
        if (poly->coeff > 0 && poly != NULL)
            printf("+");
        printf("%d", poly->coeff);
        if (poly->exp != 0)
            printf("x^%d", poly->exp);
        poly = poly->next;
    }
    printf("\n");
}

Term* addPoly(Term* a, Term* b) {
    Term* result = NULL;
    while (a != NULL || b != NULL) {
        if (a != NULL && (b == NULL || a->exp > b->exp)) {
            insertTerm(&result, a->coeff, a->exp);
            a = a->next;
        } else if (b != NULL && (a == NULL || b->exp > a->exp)) {
            insertTerm(&result, b->coeff, b->exp);
            b = b->next;
        } else {
            insertTerm(&result, a->coeff + b->coeff, a->exp);
            a = a->next;
            b = b->next;
        }
    }
    return result;
}

Term* multiplyPoly(Term* a, Term* b) {
    Term* result = NULL;
    for (Term* pa = a; pa != NULL; pa = pa->next) {
        for (Term* pb = b; pb != NULL; pb = pb->next) {
            insertTerm(&result, pa->coeff * pb->coeff, pa->exp + pb->exp);
        }
    }
    return result;
}

void freePoly(Term* poly) {
    while (poly != NULL) {
        Term* temp = poly;
        poly = poly->next;
        free(temp);
    }
}

Term* dividePoly(Term* a, Term* b) {
    Term* result = NULL;
    Term* tempA = NULL;

    // a를 복사
    for (Term* curr = a; curr != NULL; curr = curr->next)
        insertTerm(&tempA, curr->coeff, curr->exp);

    while (tempA != NULL && tempA->exp >= b->exp) {
        int coeff = tempA->coeff / b->coeff;
        int exp = tempA->exp - b->exp;
        insertTerm(&result, coeff, exp);

        // 나눗셈 결과 * 나누는 다항식 → 뺄셈할 다항식 생성
        Term* tempB = NULL;
        for (Term* curr = b; curr != NULL; curr = curr->next)
            insertTerm(&tempB, -1 * coeff * curr->coeff, curr->exp + exp);

        Term* newTempA = addPoly(tempA, tempB);

        freePoly(tempB);
        freePoly(tempA);
        tempA = newTempA;
    }

    freePoly(tempA);
    return result;
}





int main() {
    int T, coeff, exp;
    Term* poly = NULL;

    printf("항의 개수: ");
    scanf("%d", &T);
    
    for (int i = 0; i < T; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly, coeff, exp);
    }

    printf("입력된 다항식: ");
    printPoly(poly);


    // 예시: 두 번째 다항식 입력 후 연산
    printf("두 번째 다항식 항의 개수: ");
    scanf("%d", &T);
    Term* poly2 = NULL;
    for (int i = 0; i < T; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly2, coeff, exp);
    }

    printf("두 번째 다항식: ");
    printPoly(poly2);

    Term* sum = addPoly(poly, poly2);
    printf("덧셈 결과: ");
    printPoly(sum);

    Term* product = multiplyPoly(poly, poly2);
    printf("곱셈 결과: ");
    printPoly(product);

    Term* quotient = dividePoly(poly, poly2);
    printf("나눗셈 결과 (몫): ");
    printPoly(quotient);

    return 0;
}
