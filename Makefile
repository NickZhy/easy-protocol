ezpcc:	lexer.l parser.yy ast.hh ast.cc helper.hh helper.cc main.cc
	bison -d parser.yy
	flex --header-file=lexer.lex.hh -olexer.lex.cc lexer.l
	g++ -o $@ parser.tab.cc lexer.lex.cc ast.cc helper.cc main.cc

.PHONY: clean
clean:
	rm -f *.tab.* *.lex.* ezpcc 
