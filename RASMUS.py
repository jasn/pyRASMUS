#!/usr/bin/python
import rasmus.lexer
import rasmus.parser
import rasmus.error
import rasmus.jsonPrinter
import rasmus.codegen
import rasmus.charRanges
import rasmus.firstParse
import rasmus.code
import rasmus.AST
import os

def run_file(path):
    myFile = open(path)
    code = rasmus.code.Code(myFile.read(), "hat")
    e = rasmus.error.Error(code)
    p = rasmus.parser.Parser(e, code)
    AST = p.parse()
    rasmus.charRanges.CharRanges().visit(AST)
    rasmus.firstParse.FirstParse(e, code).visit(AST)
    return 0

def hat(hat):
    return True

def run_terminal():
    code = rasmus.code.Code("", "Interpreted")
    e = rasmus.error.Error(code)
    typeChecker = rasmus.firstParse.FirstParse(e, code)
    outerLus = [{}]
    theCode = ""
    incomplete = ""
    codegen = rasmus.codegen.Codegen()
    sequenceExpNode = rasmus.AST.SequenceExp()    
    while True:       
        if incomplete:
            os.write(0, ".... ")
        else:
            os.write(0, ">>>> ")
        line = os.read(2, 1024*10)
        if len(line) == 0: break
        newCode = theCode + incomplete + line
        code.setCode(newCode)
        p = rasmus.parser.Parser(e, code, True, len(theCode))
        try:
            errorsPrior = e.numberOfErrors
            AST = p.parse()
            if not isinstance(AST, rasmus.AST.InvalidExp):
                AST=AST.exp
                rasmus.charRanges.CharRanges().visit(AST)
                sequenceExpNode.sequence.append(AST)
                typeChecker.setLus(outerLus)
                typeChecker.visit(AST)
                errorsNow = e.numberOfErrors
                if errorsNow == errorsPrior:
                    outerLus = typeChecker.getLus()
                    theCode = newCode + ";\n"
                    ol = len(codegen.methods[0])
                    codegen.visit(AST)
                    s = ""
                    for c in codegen.methods[0][ol:]:
                        s += "%d "%ord(c)
                    print s
                else:
                    sequenceExpNode.sequence.pop()
                incomplete = ""
        except rasmus.parser.IncompleteInputException:
            incomplete += line + "\n"    
    return 0

def entry_point(argv):
    if len(argv) == 1:
        return run_terminal()

    if len(argv) == 2:
        return run_file(argv[1])

    return 1

def target(*args):
    return entry_point, None

if __name__ == "__main__":
    import sys
    entry_point(sys.argv)

