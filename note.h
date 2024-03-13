extern int output_graph;
extern int output_html;

void init_graph(void);
void write_graph(void);
void close_graph(void);
void add_link_to_graph(char *tail_name, char *head_name);
