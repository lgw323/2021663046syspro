#include <stdio.h>

int main()
{
    char word;
    while(1)
    {
        printf("문자 입력: ");
        scanf(" %c", &word);
        if(word == '0') {break;}
        else
        {
            if('a' <= word && word <= 'z')
            {
                char little_word = (char)(word - 32);
                printf("%c의 대문자는 %c입니다.\n", word, little_word);
            }
            else if('A' <= word && word <= 'Z')
            {
                char little_word = (char)(word + 32);
                printf("%c의 소문자는 %c입니다.\n", word, little_word);
            }
        }
    }
    return 0;
}
