#include "llvm/IR/Function.h"
#include "llvm/IR/Attributes.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

  struct FirstPass : public FunctionPass {
    static char ID; 
    FirstPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &func) {
      func.addFnAttr(Attribute::AlwaysInline);
      if (func.getName() == "evalS")  {
        for (Function::iterator bblk = func.begin(), e = func.end(); bblk != e; ++bblk) {
          errs() << "Basic block (name=" << bblk->getName() << ") has " << bblk->size() << " instructions:\n";
          
          for (BasicBlock::iterator instr = bblk->begin(), e = bblk->end(); instr != e; ++instr)
            errs() << "   " << *instr << "\n";
        }
      }
      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesAll();
    }
  };
}

char FirstPass::ID = 0;
static RegisterPass<FirstPass>
Y("firstpass", "First test of writing a custom optimization");
