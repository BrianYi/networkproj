#pragma once
//set encoding:utf-8
#include <cstddef>
#include <iomanip>
#include <map>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace Z
{
    const int MaxSize = 200;
    class basic_mstring {
        public:
            //9.3.1
            typedef size_t					size_type_;
            typedef char					*iterator_;
            typedef const char				*const_iterator_;
            typedef char					*reverse_iterator_;
            typedef const char				*const_reverse_iterator_;
            typedef int						difference_type_;
            typedef char					value_type_;
            typedef char					&reference_;
            typedef const value_type_	    &const_reference_;
        public:
            enum special_value_ {
                npos_value_			= -1,
                once_times_value_	= 1,
                more_times_value_	= 2
            };
            static const size_type_ npos_ = npos_value_;
        public:
            //构造函数
            basic_mstring(
                    void):alphabet_category_times(once_times_value_)
            {
                this->pStr = this->m_pStr;
                m_pStr[0] = '\0';
            }
            ~basic_mstring(
                    void)
            {
            }
            // 9.6
            basic_mstring(
                    const value_type_* cp):alphabet_category_times(once_times_value_)
            {
                this->pStr = this->m_pStr;
                m_pStr[0] = '\0';

                while ((*this->pStr++ = *cp++));
                this->pStr = this->m_pStr;
            }
            basic_mstring(
                    const basic_mstring& s2):alphabet_category_times(once_times_value_)
            {
                this->pStr = this->m_pStr;
                m_pStr[0] = '\0';

                while ((*this->pStr++ = *s2.pStr++));
                this->pStr = this->m_pStr;
                s2.pStr = const_cast<value_type_*>(s2.m_pStr);
                this->m_alphabet_category = s2.m_alphabet_category;
            }
            //9.6.1
            basic_mstring(
                    const value_type_* cp, 
                    const size_type_& n):alphabet_category_times(once_times_value_)
        {
            this->pStr = this->m_pStr;
            m_pStr[0] = '\0';

            size_type_ len = n;
            while (len--)
                *this->pStr++ = *cp++;
            *this->pStr = '\0';
            this->pStr = this->m_pStr;
        }
            basic_mstring(
                    const basic_mstring& s2, 
                    const size_type_& pos2):alphabet_category_times(once_times_value_)
        {
            this->pStr = this->m_pStr;
            m_pStr[0] = '\0';

            s2.pStr = const_cast<value_type_*>(s2.m_pStr + pos2);
            while ((*this->pStr++ = *s2.pStr++));
            this->pStr = this->m_pStr;
            s2.pStr = const_cast<value_type_*>(s2.m_pStr);
        }
            basic_mstring(
                    const basic_mstring& s2, 
                    const size_type_& pos2, 
                    const size_type_& len2):alphabet_category_times(once_times_value_) 
        {
            this->pStr = this->m_pStr;
            m_pStr[0] = '\0';

            s2.pStr = const_cast<value_type_*>(s2.m_pStr + pos2);
            size_type_ len = len2;
            while (len--)
                *this->pStr++ = *s2.pStr++;
            *this->pStr = '\0';
            this->pStr = this->m_pStr;
            s2.pStr = const_cast<value_type_*>(s2.m_pStr);
        }
            //类型定义
        public:
            //9.3.2
            iterator_ begin_(
                    void)
            {
                return this->m_pStr;
            }
            //
            iterator_ end_(
                    void)
            {
                return &this->m_pStr[this->size_()+1];
            }
            //
            iterator_ rbegin_(
                    void)
            {
                return end_();
            }
            iterator_ rend_(
                    void)
            {
                return begin_();
            }
            //9.3.3
            void push_back_(
                    const_reference_ t)
            {
                this->insert_(this->begin_() + this->size_() - 1, t);
            }
            void push_front_(
                    const_reference_ t)
            {
                this->insert_(this->begin_(), t);
            }
            //iterator_ insert_(iterator_ p, value_type_ t);
            //9.3.5
            size_type_ size_(
                    void) const
            {
                return this->strlen_(this->m_pStr);
            }
            size_type_ max_size_(
                    void) const
            {
                return MaxSize;
            }
            bool empty_(
                    void)
            {
                return bool(!this->size_());
            }
            //
            void resize_(
                    const size_type_& n, const_reference_ t = 0)
            {
                if (n > this->size_()) this->insert_(this->end_() - 1, n - this->size_(), t);
                else this->erase_(this->begin_() + n, this->end_() - 1);
            }
            //9.3.6
            reference_ back_(
                    void)
            {
                return m_pStr[this->size_()-1];
            }
            //
            reference_ front_(
                    void) 
            {
                return m_pStr[0];
            }
            // [] 运算符重载
            reference_ at_(
                    const size_type_& n)
            {
                if (n >= this->size_())
                    throw runtime_error("Out of range!");
                return m_pStr[n];
            }
            //9.3.7
            iterator_ erase_(
                    const_iterator_ p)
            {
                iterator_ tmp = const_cast<iterator_>(p);
                this->pStr = const_cast<iterator_>(p);
                iterator_ p1 = const_cast<iterator_>(p);
                while ((*this->pStr++ = *++p1));
                return tmp;
            }
            //
            iterator_ erase_(
                    const_iterator_ b, const_iterator_ e)
            {
                iterator_ tmp = const_cast<iterator_>(b);
                this->pStr = const_cast<iterator_>(b);
                iterator_ p1 = const_cast<iterator_>(e);
                while ((*this->pStr++ = *p1++));
                return tmp;
            }
            //
            void clear_(
                    void)
            {
                this->m_pStr[0] = '\0';
            }
            void pop_back_(
                    void)
            {
                this->erase_(this->begin_() + this->size_() - 1);
            }
            void pop_front_(
                    void)
            {
                this->erase_(this->begin_());
            }
            //9.3.8
            // = ÔËËã·ûÎ´ÖØÔØ
            void swap_(
                    basic_mstring& c2)
            {
                basic_mstring temp;
                temp = *this;
                *this = c2;
                c2 = temp;
            }
            void assign_(
                    const_iterator_ b, 
                    const_iterator_ e)
            {
                this->clear_();
                this->insert_(this->begin_(), b, e);
            }

            void assign_(
                    const size_type_& n, 
                    const_reference_ t) 
            {
                this->clear_();
                this->insert_((size_type_)0, n, t);
            }
            //9.6.2 µü´úÆ÷²Ù×÷
            iterator_ insert_(
                    iterator_ p, 
                    const_reference_ t)
            {
                iterator_ tmp = p;
                iterator_ p1 = this->end_()-1;
                this->pStr = this->end_();
                while (*this->pStr-- = *p1--,p1 != p-1);
                *p = t;
                return tmp;
            }
            //
            void insert_(
                    iterator_ p, 
                    const size_type_& n, 
                    const_reference_ t)
            {
                size_type_ i = n;
                while (i--)
                    this->insert_(p,t);
            }
            void insert_(
                    iterator_ p, 
                    const_iterator_ b, 
                    const_iterator_ e)
            {
                iterator_ begin = const_cast<iterator_>(b);
                iterator_ end = const_cast<iterator_>(e);
                while (begin != end)
                    this->insert_(p++,*begin++);
            }
            //ÏÂ±ê²Ù×÷
            basic_mstring& insert_(
                    const size_type_ pos, 
                    const size_type_& n, 
                    const_reference_ c)
            {
                size_type_ len = n;
                while (len--)
                    this->insert_(this->begin_() + pos, c);
                return *this;
            }

            basic_mstring& insert_(
                    const size_type_& pos, 
                    basic_mstring& s2)
            {
                this->insert_(this->begin_() + pos, s2.begin_(), s2.end_() - 1);
                this->pStr = this->m_pStr;
                return *this;
            }

            basic_mstring& insert_(
                    const size_type_& pos, 
                    basic_mstring& s2, 
                    const size_type_& pos2, 
                    const size_type_& len)
            {
                this->insert_(this->begin_() + pos, s2.begin_() + pos2, s2.begin_() + pos2 + len);
                return *this;
            }

            basic_mstring& insert_(
                    const size_type_& pos, 
                    const_iterator_ cp, 
                    const size_type_& len)
            {
                this->insert_(this->begin_() + pos, cp, cp + len);
                return *this;
            }

            basic_mstring& insert_(
                    const size_type_& pos, 
                    const_iterator_ cp)
            {
                this->insert_(pos, cp, strlen_(cp));
                return *this;
            }

            //9.6.3
            basic_mstring substr_(
                    const size_type_& pos, 
                    const size_type_& n)
            {
                basic_mstring temp;
                this->pStr = this->m_pStr;
                this->pStr += pos;
                size_type_ len = n;
                size_type_ i = 0;
                while (len--)
                    temp.m_pStr[i++] = *this->pStr++;
                temp.m_pStr[i] = '\0';
                temp.pStr = temp.m_pStr;
                return temp;
            }
            basic_mstring substr_(
                    const size_type_& pos)
            {
                basic_mstring temp;
                this->pStr = this->m_pStr;
                this->pStr += pos;
                while ((*temp.pStr++ = *this->pStr++));
                temp.pStr = temp.m_pStr; //
                return temp;
            }
            //9.6.4
            size_type_ find_(
                    const value_type_& c, 
                    const size_type_& pos = 0)
            {
                size_type_ len = this->size_();
                size_type_ i;
                for (i = pos; i < len; i++)
                    if (this->m_pStr[i] == c) return i;
                return this->npos_;
            }
            size_type_ find_(
                    const basic_mstring& s2, 
                    const size_type_& pos = 0)
            {
                size_type_ len1 = this->size_();
                size_type_ len2 = s2.size_();
                size_type_ i;
                for (i = pos; i < len1; i++)
                    if (this->substr_(i, len2) == s2) return i;
                return this->npos_;
            }
            size_type_ find_(
                    const_iterator_ cp, 
                    const size_type_& pos = 0)
            {
                return this->find_(static_cast<basic_mstring>(cp), pos);
            }
            size_type_ find_(
                    const_iterator_ cp, 
                    const size_type_& pos, 
                    const size_type_& n)
            {
                return this->find_(static_cast<basic_mstring>(cp).substr_(0, n), pos);
            }
            size_type_ find_first_of_(
                    const size_type_& c, 
                    const size_type_& pos = 0)
            {
                return this->find_(c, pos);
            }
            size_type_ find_first_of_(
                    const basic_mstring& s2, 
                    const size_type_& pos = 0)
            {
                size_type_ len1 = this->size_();
                size_type_ len2 = s2.size_();
                for (size_type_ i = pos; i < len1; i++) {
                    for (size_type_ j = 0; j < len2; j++)
                        if (this->m_pStr[i] == s2.m_pStr[j])
                            return i;
                }
                return this->npos_;
            }
            size_type_ find_first_of_(
                    const_iterator_ cp, 
                    const size_type_& pos = 0)
            {
                return this->find_first_of_(static_cast<basic_mstring>(cp), pos);
            }
            size_type_ find_first_of_(
                    const_iterator_ cp, 
                    const size_type_& pos, 
                    const size_type_& n)
            {
                return this->find_first_of_(static_cast<basic_mstring>(cp).substr_(0, n), pos);
            }
            //
            const map<value_type_, int> alphabet_category_(
                    void)
            {
                if (this->alphabet_category_times == this->once_times_value_) {
                    this->alphabet_category_times = this->more_times_value_;
                    for (basic_mstring::iterator_ iter = this->begin_(); iter != this->end_(); iter++)
                        if (*iter)
                            ++this->m_alphabet_category[*iter];
                    return this->m_alphabet_category;
                }
                return this->m_alphabet_category;
            }
            const basic_mstring& alphabet_sort_(
                    void)
            {
                map<value_type_, int> tmp = this->alphabet_category_();
                this->clear_();
                for (map<value_type_, int>::iterator iter = tmp.begin(); iter != tmp.end(); iter++) {
                    size_type_ word_times = iter->second;
                    this->insert_(this->size_(), word_times, iter->first);
                }
                return *this;
            }
            //
            size_type_ alphabet_times_(
                    const value_type_& c)
            {
                for (map<value_type_, int>::iterator iter = this->m_alphabet_category.begin(); iter != this->m_alphabet_category.end(); iter++)
                    if (c == iter->first)
                        return iter->second;
                cerr << "Doesn't have this alphabet! Function will return -1!" << endl;
                return -1;
            }
            //
            size_type_ alphabet_max_times_(
                    void)
            {
                int max_times = 0;
                for (map<value_type_, int>::iterator iter = this->m_alphabet_category.begin(); iter != this->m_alphabet_category.end(); iter++)
                    if (max_times < iter->second)
                        max_times = iter->second;
                return max_times;
            }
            //
            void display_alphabet_category_(
                    void)
            {
                this->alphabet_category_();
                cout << "Alphabet times" << endl;
                for (map<value_type_, int>::iterator iter = this->m_alphabet_category.begin(); iter != this->m_alphabet_category.end(); iter++)
                    cout << setiosflags(ios::left) << setw(9) << iter->first << setw(8) << iter->second << endl;
            }
            const value_type_* c_str_(
                    void)
            {
                return this->m_pStr;
            }
            // ÔËËã·ûÖØÔØ
            friend istream& operator >> (
                    istream& in, 
                    basic_mstring& s)
            {
                in >> s.m_pStr;
                return in;
            }
            friend ostream& operator << (
                    ostream& out, 
                    basic_mstring& s)
            {
                out << s.m_pStr;
                return out;
            }
            reference_ operator [](
                    const size_type_& pos)
            {
                if (pos > this->size_())
                    throw runtime_error("Out of range!");
                return this->m_pStr[pos];
            }
            // ÔËËã·ûÖØÔØ +¡¢+=¡¢>¡¢<¡¢==¡¢!=
            friend basic_mstring operator + (
                    basic_mstring s1, 
                    basic_mstring s2)
            {
                return s1.insert_(s1.size_(), s2);
            }
            friend basic_mstring& operator += (
                    basic_mstring& s1, 
                    basic_mstring s2)
            {
                return s1.insert_(s1.size_(),s2);
            }
            friend bool operator > (
                    const basic_mstring& s1,
                    const basic_mstring& s2)
            {
                basic_mstring::size_type_ len1 = s1.size_();
                basic_mstring::size_type_ len2 = s2.size_();
                basic_mstring::size_type_ min_len = len1 < len2 ? len1 : len2;
                basic_mstring::size_type_ i;
                for (i = 0; i <= min_len; i++) {
                    if (s1.m_pStr[i] > s2.m_pStr[i])
                        return true;
                    else if (s1.m_pStr[i] == s2.m_pStr[i]) continue;
                    else return false;
                }
                return false;
            }
            friend bool operator < (
                    const basic_mstring& s1,
                    const basic_mstring& s2)
            {
                basic_mstring::size_type_ len1 = s1.size_();
                basic_mstring::size_type_ len2 = s2.size_();
                basic_mstring::size_type_ min_len = len1 < len2 ? len1 : len2;
                basic_mstring::size_type_ i;
                for (i = 0; i <= min_len; i++) {
                    if (s2.m_pStr[i] > s1.m_pStr[i])
                        return true;
                    else if (s2.m_pStr[i] == s1.m_pStr[i]) continue;
                    else return false;
                }
                return false;
            }
            friend bool operator == (
                    const basic_mstring& s1,
                    const basic_mstring& s2)
            {
                basic_mstring::size_type_ len1 = s1.size_();
                basic_mstring::size_type_ len2 = s2.size_();
                basic_mstring::size_type_ min_len = len1 < len2 ? len1 : len2;
                basic_mstring::size_type_ i;
                for (i = 0; i <= min_len; i++) {
                    if (s1.m_pStr[i] != s2.m_pStr[i])
                        return false;
                }
                return true;
            }
            friend bool operator != (
                    const basic_mstring& s1,
                    const basic_mstring& s2)
            {
                return !(s1 == s2);
            }
        protected:
            size_type_ alphabet_category_times;
            value_type_ m_pStr[MaxSize];
            mutable value_type_* pStr;
            map<value_type_, int> m_alphabet_category;		
        private:
            size_type_ strlen_(const value_type_* str) const
            {
                size_type_ len=0;
                const value_type_* p = str;
                while ( *p++ ) ++len;
                return len;
            }
    };
}
