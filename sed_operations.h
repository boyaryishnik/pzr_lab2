#ifndef SED_OPERATIONS_H
#define SED_OPERATIONS_H

void replace_text(const char *filename, const char *old_text, const char *new_text);
void delete_lines(const char *filename, const char *regex_pattern);
void add_prefix(const char *filename, const char *prefix);
void add_suffix(const char *filename, const char *suffix);

#endif // SED_OPERATIONS_H
