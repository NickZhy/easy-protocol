ezpcc:	lexer.ll parser.yy ast.hh ast.cc helper.hh helper.cc main.cc visitor.hh visitor.cc
	bison -d parser.yy
	flex --header-file=lexer.lex.hh -olexer.lex.cc lexer.ll
	g++ -Wall -ggdb3 -o $@ parser.tab.cc lexer.lex.cc ast.cc helper.cc main.cc visitor.cc

.PHONY: clean
clean:
	rm -f *.tab.* *.lex.* ezpcc 
