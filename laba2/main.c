#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>
#include <math.h>

struct table {
    char firstName[20];
    int res[3];
    int exp[3];
};

void input_validation(struct table new, int *flag) {
    if (new.res[0] > 31 || new.exp[0] > 31 || new.res[0] < 1 || new.exp[0] < 1
        || new.res[1] > 12 || new.exp[1] > 12 || new.res[1] < 1 || new.exp[1] < 1
        || new.res[2] > 2021 || new.exp[2] > 2021 || new.res[2] < 1900 || new.exp[2] < 1900
        || new.exp[2] > new.res[2] || (new.exp[1] == 2) && (new.exp[0] == 30) ||
        (new.res[1] == 2) && (new.res[0] == 30)) {
        printf("Unavailable input\n");
        *flag = 1;
    }
}

struct table Input(int *flag) {
    struct table new;
    printf("Enter Family\n");
    scanf("%s", new.firstName);
    printf("Enter receipt date (dd mm yy)\n");
    scanf("%d", &new.res[0]);
    scanf("%d", &new.res[1]);
    scanf("%d", &new.res[2]);
    printf("Enter date of expulsion (dd mm yy)\n");
    scanf("%d", &new.exp[0]);
    scanf("%d", &new.exp[1]);
    scanf("%d", &new.exp[2]);
    input_validation(new, flag);
    return (new);
}

void Output(struct table new) {
    printf("First name is %s\n", new.firstName);
    printf("Receipt date is %d %d %d\n", new.res[0], new.res[1], new.res[2]);
    printf("Date of expulsion is %d %d %d\n\n", new.exp[0], new.exp[1], new.exp[2]);
}

void File_write(struct table new, int *flag, int count, char *name) {
    FILE *fp;
    if ((fp = fopen(name, "r+w")) == NULL) {
        printf("Can't open file 'write.txt'\n");
        *flag = 1;
    }
    struct table buf;
    for (int i = 0; i < count; i++) {
        fscanf(fp, "%s", buf.firstName);
        fscanf(fp, "%*s%*s%d %d %d", &buf.res[0], &buf.res[1], &buf.res[2]);
        fscanf(fp, "%*s%*s%*s%d %d %d\n", &buf.exp[0], &buf.exp[1], &buf.exp[2]);
    }
    fprintf(fp, "%s\n", new.firstName);
    fprintf(fp, "Receipt date: %d %d %d\n", new.res[0], new.res[1], new.res[2]);
    fprintf(fp, "Date of expulsion: %d %d %d\n", new.exp[0], new.exp[1], new.exp[2]);
    fclose(fp);
}

struct table *File_read(int *flag, int *len) {
    struct table *new = (struct table *) malloc(2 * sizeof(struct table));
    FILE *fp;
    if ((fp = fopen("read.txt", "r")) == NULL) {
        printf("Can't open file 'read.txt'\n");
        *flag = 1;
    }
    while (fscanf(fp, "%s", new[*len].firstName) == 1) {
        fscanf(fp, "%*s%*s%d %d %d", &new[*len].res[0], &new[*len].res[1], &new[*len].res[2]);
        fscanf(fp, "%*s%*s%*s%d %d %d\n", &new[*len].exp[0], &new[*len].exp[1], &new[*len].exp[2]);
        new = (struct table *) realloc(new, (*len + 2) * sizeof(struct table[2]));
        (*len)++;
    }
    fclose(fp);
    for (int i = 0; i < *len; ++i) input_validation(new[i], flag);
    return new;
}

int Find_int(struct table *new, int count, int value) {
    int delta[2] = {INT_MAX, 0};
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (new[i].res[j] == value) return new[i].res[j];
            if (new[i].exp[j] == value) return new[i].exp[j];
            if (abs(value - new[i].res[j]) < delta[0]) {
                delta[0] = abs(value - new[i].res[j]);
                delta[1] = i;
            }
            if (abs(value - new[i].exp[j]) < delta[0]) {
                delta[0] = abs(value - new[i].exp[j]);
                delta[1] = i;
            }
        }
    }
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (abs(value - new[delta[1]].exp[j]) == delta[0]) {
                printf("%s\nExpulsion date = %d\n", new[delta[1]].firstName, new[delta[1]].exp[j]);
                return 0;
            }
            if (abs(value - new[delta[1]].res[j]) == delta[0]) {
                printf("%s\nReceipt date = %d\n", new[delta[1]].firstName, new[delta[1]].res[j]);
                return 0;
            }
        }
    }
    return 0;
}

int Find_char(struct table *new, int count, char *value) {
    int match, rez = 0;
    for (int i = 0; i < count; ++i) {
        match = 0;
        for (int j = 0; j < strlen(value); ++j) {
            if (new[i].firstName[0] == value[j]) match++;
        }
        if (match > rez) rez = match;
    }
    for (int i = 0; i < count; ++i) {
        match = 0;
        for (int j = 0; j < strlen(value); ++j) {
            if (new[i].firstName[0] == value[j]) match++;
        }
        if (match == rez) {
            printf("%s\n", new[i].firstName);
            return 0;
        }
    }
    return 0;
}

void Sort(struct table *new, int count, int select) {
    int i, j;
    struct table temp;
    for (i = 0; i < count - 1; i++)
        for (j = 0; j < count - i - 1; j++) {
            for (int k = 0; k < 3; ++k) {
                switch (select) {
                    case 1:
                        if ((int) new[j].firstName[0] > (int) new[j + 1].firstName[0]) {
                            temp = new[j];
                            new[j] = new[j + 1];
                            new[j + 1] = temp;

                        }
                        break;
                    case 2:
                        if (new[j].res[k] > new[j + 1].res[k]) {
                            temp = new[j];
                            new[j] = new[j + 1];
                            new[j + 1] = temp;

                        }
                        break;
                    case 3:
                        if (new[j].exp[k] > new[j + 1].exp[k]) {
                            temp = new[j];
                            new[j] = new[j + 1];
                            new[j + 1] = temp;

                        }
                        break;
                    default:
                        printf("Error\n");
                        break;
                }
            }
        }
    for (int k = 0; k < count; ++k)
        File_write(new[k], 0, k, "sorted.txt");
}

void Delete_value(struct table *new, const int *count) {
    if (count[1] == 1) strcpy(new[count[0]].firstName, "");
    if (count[1] == 2) new[count[0]].res[count[2]] = 0;
    if (count[1] == 3) new[count[0]].exp[count[2]] = 0;
}

struct table *Delete_object(struct table *new, const int *count, int *len) {
    for (int i = *count; i < *len; ++i) new[i] = new[i + 1];
    (*len)--;
    new = (struct table *) realloc(new, *len * sizeof(struct table));
    return new;
}

int Edit_value(struct table *new, const int *count, int iValue, char *cValue) {
    if (count[1] == 1) strcpy(new[count[0]].firstName, cValue);
    if (count[1] == 2) new[count[0]].res[count[2]] = iValue;
    if (count[1] == 3) new[count[0]].exp[count[2]] = iValue;
    return 0;
}

int Interface(struct table *a, int len, int *select_id, int bool, int *iValue, char *cValue) {
    for (int i = 0; i < len; ++i) {
        printf("#%d - %s\n", i + 1, a[i].firstName);
    }
    printf("Chose user number: ");
    scanf("%d", &select_id[0]);
    select_id[0]--;
    if ((select_id[0] < 1) || (select_id[0] > len + 1)) {
        printf("Unavailable input\n");
        return 1;
    }
    printf("#1 %s\n"
           "#2 %d %d %d\n"
           "#3 %d %d %d\n", a[select_id[0]].firstName, a[select_id[0]].res[0], a[select_id[0]].res[1],
           a[select_id[0]].res[2], a[select_id[0]].exp[0], a[select_id[0]].exp[1], a[select_id[0]].exp[2]);

    printf("Select the field: ");
    scanf("%d", &select_id[1]);
    if ((select_id[1] < 1) || (select_id[1] > 3)) {
        printf("Unavailable input\n");
        return 1;
    }
    if (select_id[1] == 1) {
        Delete_value(a, select_id);
        if (bool == 1) {
            printf("Enter a value: ");
            scanf("%s", cValue);
        }
    } else {
        printf("Select cell\n#1 dd\n#2 mm\n#3 yy\n");
        scanf("%d", &select_id[2]);
        select_id[2]--;
        if ((select_id[2] < 1) || (select_id[2] > 3)) {
            printf("Unavailable input\n");
            return 1;
        }
        if (bool == 1) {
            printf("Enter a value: ");
            scanf("%d", iValue);
        }
    }
    return 0;
}

void Average(struct table *new, int len) {
    double delta[3];
    for (int j = 0; j < 3; ++j) delta[j] = 0;
    for (int i = 0; i < len; ++i)
        for (int j = 0; j < 3; ++j)
            delta[j] += abs(new[i].res[j] - new[i].exp[j]);
    for (int j = 0; j < 3; ++j) {
        delta[j] /= len;
        printf("%.2f ", round(delta[j] * 1000) / 1000);
    }
    printf("\n");
}

int check(int select, int a, int b) {
    if (select < a || select > b) {
        printf("Unavailable input\n");
        return 1;
    } else return 0;
}

int Ask() {
    int flag = 0, select, fInt, len = 0, rez, iValue, buf = 0;
    int select_id[3];
    char *cValue = (char *) malloc(20 * sizeof(char));
    char fChar[20];
    struct table *a;
    while (1) {
        printf("1 <->Enter table from console?\n"
               "2 <->Read table from file?\n"
               "3 <->Show tables?\n"
               "4 <->Write tables in file?\n"
               "5 <->Sort table?\n"
               "6 <->Find value in table?\n"
               "7 <->Delete value?\n"
               "8 <->Delete object?\n"
               "9 <->Edit value?\n"
               "10<->Show the average length of study?\n"
               "11<->Exit\n");
        scanf("%d", &select);
        if (check(select, 1, 12)) return 0;
        if ((len == 0) && ((select == 3) || (select > 4) && (select < 11))) {
            printf("\tVoid table. Add objects!\n\n");
            continue;
        }
        switch (select) {
            case 1:
                printf("How many table do you want to enter?\n");
                scanf("%d", &buf);
                len += buf;
                a = (struct table *) realloc(a, sizeof(struct table) * len);
                for (int i = len - buf; i < len; ++i) {
                    a[i] = Input(&flag);
                    if (flag == 1) return 0;
                }
                break;
            case 2:
                a = File_read(&flag, &len);
                printf("Successful!\n");
                break;
            case 3:
                for (int i = 0; i < len; ++i) Output(a[i]);
                break;
            case 4:
                for (int i = 0; i < len; ++i) File_write(a[i], &flag, i, "write.txt");
                break;
            case 5:
                printf("Select sort:\n"
                       "1-Sort by last name\n"
                       "2-Sort by date of receipt\n"
                       "3-Sort by expiration date\n");
                scanf("%d", &select);
                if (check(select, 1, 3)) return 0;
                Sort(a, len, select);
                for (int i = 0; i < len; ++i) {
                    printf("%s\n", a[i].firstName);
                    switch (select) {
                        case 1:
                            continue;
                        case 2:
                            printf("%d %d %d\n", a[i].res[0], a[i].res[1], a[i].res[2]);
                            break;
                        case 3:
                            printf("%d %d %d\n", a[i].exp[0], a[i].exp[1], a[i].exp[2]);
                            break;
                        default:
                            return 0;
                    }
                }
                break;
            case 6:
                printf("What do you want to find int or char?\n"
                       "1-Int\n"
                       "2-Char\n");
                scanf("%d", &select);
                if (check(select, 1, 2)) return 0;
                printf("Enter value\n");
                switch (select) {
                    case 1:
                        scanf("%d", &fInt);
                        Find_int(a, len, fInt);
                        break;
                    case 2:
                        scanf("%s", fChar);
                        Find_char(a, len, fChar);
                        break;
                    default:
                        printf("Unavailable input\n");
                        return 0;
                }
                break;
            case 7:
                rez = Interface(a, len, select_id, 0, 0, 0);
                if (rez == 1) return 0;
                if (rez == 2) Delete_value(a, select_id);
                printf("#1 %s\n"
                       "#2 %d %d %d\n"
                       "#3 %d %d %d\n", a[select_id[0]].firstName, a[select_id[0]].res[0], a[select_id[0]].res[1],
                       a[select_id[0]].res[2], a[select_id[0]].exp[0], a[select_id[0]].exp[1],
                       a[select_id[0]].exp[2]);
                break;
            case 8:
                for (int i = 0; i < len; ++i) {
                    printf("####%d####\n", i);
                    printf("%s\n", a[i].firstName);
                }
                printf("Enter the object number to be deleted\n");
                scanf("%d", &select_id[2]);
                if (check(select_id[2], 1, len)) return 0;
                a = Delete_object(a, &select_id[2], &len);
                for (int i = 0; i < len; ++i) {
                    printf("####%d####\n", i);
                    printf("%s\n", a[i].firstName);
                }
                break;
            case 9:
                rez = Interface(a, len, select_id, 1, &iValue, cValue);
                if (rez == 1) return 0;
                Edit_value(a, select_id, iValue, cValue);
                printf("\n%s\n"
                       "%d %d %d\n"
                       "%d %d %d\n", a[select_id[0]].firstName, a[select_id[0]].res[0], a[select_id[0]].res[1],
                       a[select_id[0]].res[2], a[select_id[0]].exp[0], a[select_id[0]].exp[1],
                       a[select_id[0]].exp[2]);
                break;
            case 10:
                printf(" dd   mm   yy\n");
                Average(a, len);
                break;
            case 11:
                return 0;
            default:
                printf("Unavailable input\n");
        }
    }
}

int main() {
    if (!Ask()) return 0;
}