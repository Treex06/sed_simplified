#ifndef SED_OPERATIONS_H
#define SED_OPERATIONS_H

void replace_text(const char *filename, const char *old_text, const char *new_text);
void delete_lines(const char *filename, const char *regex_pattern);
void insert_text(const char *filename, const char *insert_text, int at_beginning);

#endif // SED_OPERATIONS_H
