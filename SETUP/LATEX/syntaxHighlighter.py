#
# DISCLAIMER:
#
# THIS SCRIPT IS TO EASE LATEX WRITING BY AUTOMATING ONLY THE SYNTAX HIGHLIGHTING BY INSERTING
# MY MACROS INSIDE THE DOCUMENT CODE. SHOULD YOU NEED ANYTHING ELSE, EITHER CODE IT YOURSELF
# OR FIND SOME OTHER TOOL!
#

from pylatexenc.latexwalker import LatexWalker, LatexEnvironmentNode
from pylatexenc.latex2text import LatexNodes2Text












map_parentheses = {
	'(': { "index": 0, "weight": +1 }, ')': { "index": 0, "weight": -1 },
	'[': { "index": 1, "weight": +1 }, ']': { "index": 1, "weight": -1 },
	'{': { "index": 2, "weight": +1 }, '}': { "index": 2, "weight": -1 }
}

map_operators = {
	"math": {
		"operators": [
			"\\sum", "\\prod", "\\coprod", "\\int", "\\lim", "\\oint", "\\iint", "\\biguplus", "\\bigcap", "\\bigcup", "\\bigoplus", "\\bigotimes", "\\bigodot", "\\bigvee", "\\bigwedge", "\\bigsqcup",
			"\\sqrt", "\\ast", "\\star", "\\cdot", "\\bullet", "\\circ", "\\bigcirc", "\\diamond", "\\times", "\\div", "\\centerdot", "\\circledast", "\\circledcirc", "\\circleddash", "\\dotplus", "\\divideontimes",
			"\\pm", "\\mp", "\\amalg", "\\odot", "\\ominus", "\\oplus", "\\oslash", "\\otimes", "\\wr", "\\Box", "\\boxplus", "\\boxminus", "\\boxtimes", "\\boxdot", "\\square", "\\cap", "\\cup", "\\uplus", "\\sqcap",
			"\\sqcup", "\\wedge", "\\vee", "\\dagger", "\\ddagger", "\\barwedge", "\\veebar", "\\curlywedge", "\\curlyvee", "\\Cap", "\\Cup", "\\bot", "\\top", "\\intercal", "\\doublebarwedge", "\\lhd", "\\rhd", "\\triangleleft",
			"\\triangleright", "\\unlhd", "\\unrhd", "\\bigtriangledown", "\\bigtriangleup", "\\setminus", "\\rightthreetimes", "\\leftthreetimes", "\\equiv", "\\cong", "\\neq", "\\sim", "\\simeq", "\\approx", "\\doteq",
			"\\propto", "\\models", "\\leq", "\\geq", "\\prec", "\\succ", "\\preceq", "\\succeq", "\\ll", "\\gg", "\\subset", "\\supset", "\\subseteq", "\\supseteq", "\\sqsubset", "\\sqsupset", "\\sqsubseteq", "\\sqsupseteq",
			"\\dashv", "\\vdash", "\\perp", "\\mid", "\\parallel", "\\bowtie", "\\Join", "\\ltimes", "\\rtimes", "\\smile", "\\frown", "\\in", "\\ni", "\\notin", "\\approxeq", "\\thicksim", "\\backsim", "\\backsimeq",
			"\\triangleq", "\\circeq", "\\bumpeq", "\\Bumpeq", "\\doteqdot", "\\thickapprox", "\\fallingdotseq", "\\risingdotseq", "\\varpropto", "\\therefore", "\\because", "\\eqcirc", "\\neq", "\\leqq", "\\geqq", "\\leqslant",
			"\\geqslant", "\\lessapprox", "\\gtrapprox", "\\lll", "\\ggg", "\\lessdot", "\\gtrdot", "\\lesssim", "\\gtrsim", "\\eqslantless", "\\eqslantgtr", "\\precsim", "\\succsim", "\\precapprox", "\\succapprox", "\\Subset",
			"\\Supset", "\\subseteqq", "\\supseteqq", "\\preccurlyeq", "\\succcurlyeq", "\\curlyeqprec", "\\curlyeqsucc", "\\blacktriangleleft", "\\blacktriangleright", "\\trianglelefteq", "\\trianglerighteq", "\\vartriangleleft",
			"\\vartriangleright", "\\lessgtr", "\\lesseqgtr", "\\lesseqqgtr", "\\gtreqqless", "\\gtreqless", "\\gtrless", "\\between", "\\backepsilon", "\\pitchfork", "\\shortmid", "\\smallfrown", "\\smallsmile", "\\Vdash", "\\vDash",
			"\\Vvdash", "\\shortparallel", "\\nshortparallel", "\\ncong", "\\nmid", "\\nparallel", "\\nshortmid", "\\nshortparallel", "\\nsim", "\\nVDash", "\\nvDash", "\\nvdash", "\\ntriangleleft", "\\ntrianglelefteq", "\\ntriangleright",
			"\\ntrianglerighteq", "\\nleq", "\\ngeq", "\\nleqq", "\\ngeqq", "\\nleqslant", "\\ngeqslant", "\\nless", "\\ngtr", "\\nprec", "\\nsucc", "\\npreceq", "\\nsucceq", "\\precnapprox", "\\succnapprox", "\\precnsim", "\\succnsim",
			"\\lnapprox", "\\gnapprox", "\\lneq", "\\gneq", "\\lneqq", "\\gneqq", "\\lnsim", "\\gnsim", "\\lvertneqq", "\\gvertneqq", "\\nsubseteq", "\\nsupseteq", "\\nsubseteqq", "\\nsupseteqq", "\\subsetneq", "\\supsetneq",
			"\\subsetneqq", "\\supsetneqq", "\\varsubsetneq", "\\varsupsetneq", "\\varsubsetneqq", "\\varsupsetneqq", "\\land", "\\lor", "\\lnot", 
		],
    "binary_operators": [
        "\\pm", "\\mp", "\\times", "\\div", "\\ast", "\\star", "\\circ", "\\bullet", "\\cdot", "\\cap", "\\cup", "\\uplus", "\\sqcap", "\\sqcup", "\\vee", "\\wedge", "\\setminus", "\\wr", "\\diamond", "\\bigtriangleup",
				"\\bigtriangledown", "\\triangleleft", "\\triangleright", "\\bigcirc", "\\dagger", "\\ddagger", "\\amalg"
    ],
    "relation_operators": [
        "\\leq", "\\prec", "\\preceq", "\\ll", "\\subset", "\\subseteq", "\\sqsubseteq", "\\in", "\\vdash", "\\geq", "\\succ", "\\succeq", "\\gg", "\\supset", "\\supseteq", "\\sqsupseteq", "\\ni", "\\dashv", "\\equiv",
				"\\sim", "\\simeq", "\\asymp", "\\approx", "\\cong", "\\neq", "\\doteq", "\\propto", "\\models", "\\perp", "\\mid", "\\parallel", "\\bowtie", "\\smile", "\\frown", "\\asymp"
    ],
    "arrows": [
        "\\leftarrow", "\\Leftarrow", "\\rightarrow", "\\Rightarrow", "\\leftrightarrow", "\\Leftrightarrow", "\\mapsto", "\\to", "\\hookleftarrow", "\\hookrightarrow", "\\leftharpoonup", "\\leftharpoondown",
				"\\rightharpoonup", "\\rightharpoondown", "\\rightleftharpoons", "\\uparrow", "\\Uparrow", "\\downarrow", "\\Downarrow", "\\updownarrow", "\\Updownarrow", "\\nearrow", "\\searrow", "\\swarrow", "\\nwarrow"
    ],
    "miscellaneous_symbols": [
        "\\forall", "\\exists", "\\neg", "\\emptyset", "\\infty", "\\partial", "\\nabla", "\\surd", "\\top", "\\bot", "\\angle", "\\triangle", "\\backslash", "\\Box", "\\Diamond", "\\imath", "\\jmath", "\\ell",
				"\\Re", "\\Im", "\\aleph", "\\hbar", "\\imath", "\\jmath", "\\ell", "\\wp", "\\Re", "\\Im", "\\mho"
    ],
    "delimiters": [
        "\\langle", "\\rangle", "\\lfloor", "\\rfloor", "\\lceil", "\\rceil", "\\lbrace", "\\rbrace", "\\lbrack", "\\rbrack", "\\vert", "\\Vert", "\\backslash", "\\slash", "\\uparrow", "\\downarrow", "\\updownarrow",
				"\\Uparrow", "\\Downarrow", "\\Updownarrow"
    ],
    "accents": [
        "\\hat", "\\check", "\\tilde", "\\acute", "\\grave", "\\dot", "\\ddot", "\\breve", "\\bar", "\\vec", "\\widehat", "\\widetilde{}"
    ]
	},
	# From C, PHP, GML and JS
	"code": {
		"arithmetic": [
			'+', '-', '*', '/', '%', '**', '.', 'sizeof'
		],
		"comparison": [
			'==', '===', '!=', '!==', '<>', '<=>', '<', '<=', '>', '>=',
		],
		"bitwise": [
			'&', '|', '^', '~', '<<', '>>', '>>>',
		],
		"logical": [
			# The GameMaker Language (GML) has a logical XOR operator, how cool is that? ^^
			'?', ':', '?:', '??',	'&&', '||',  '^^',  '!',
		],
		"assignment": [
			'=', '+=', '++', '-=', '--', '*=', '/=', '%=', '**=', '??=', '&=', '|=', '^=', '<<=', '>>=', '>>>=', '.='
		],
		"data": [
			'new', '.', '->', '::', '?.', '@', '=>', '...',
		]
	}
}

map_functions = {
	"trigonometry": [
    "\\sin", "\\cos", "\\tan", "\\csc", "\\sec", "\\cot", "\\sinh", "\\cosh", "\\tanh", "\\arcsin", "\\arccos", "\\arctan", "\\arg", "\\log", "\\ln", "\\exp",
		"\\det", "\\dim", "\\gcd", "\\hom", "\\ker", "\\lim", "\\max", "\\min", "\\sup", "\\inf", "\\deg", "\\Pr"
	],
	"exponential": [
	]
}

map_variables = {
	"greek_letters": [
		"\\alpha", "\\beta", "\\gamma", "\\delta", "\\epsilon", "\\zeta", "\\eta", "\\theta", "\\iota", "\\kappa", "\\lambda", "\\mu", "\\nu", "\\xi", "\\omicron",
		"\\pi", "\\rho", "\\sigma", "\\tau", "\\upsilon", "\\phi", "\\chi", "\\psi", "\\omega", "\\Gamma", "\\Delta", "\\Theta", "\\Lambda", "\\Xi", "\\Pi",
		"\\Sigma", "\\Upsilon", "\\Phi", "\\Psi", "\\Omega"
	],
}




def process_latex_file(file_path):
	with open(file_path, 'r') as file:
		latex_content = file.read()

	walker = LatexWalker(latex_content)
	nodes, pos, len_ = walker.get_latex_nodes()
	text = ""

	for node in nodes:
		text += f"________NODE_________: {node}\n\n"
		if False:
			if isinstance(node, LatexEnvironmentNode) and node.environmentname in ['equation', 'align']:
				original_math = latex_content[node.pos:node.pos+node.len]
				processed_math = process_math_content(original_math)
				latex_content = latex_content.replace(original_math, processed_math)
			# Handle inline math mode
			# ...

	with open("result", "w") as file:
		file.write(text)

	return 0
	with open('highlighted_' + file_path, 'w') as file:
		file.write(latex_content)



def process_math_content(math_content):
	parentheses_open = [
		0, # ()
		0, # []
		0, # {}
	]

	return

	tokens = tokenize_math(math_content)
	highlighted_content = ''
	for token in tokens:
		if is_number(token):
			highlighted_content += highlight_number(token)
		elif is_operator(token):
			highlighted_content += highlight_operator(token)
		else:
			highlighted_content += token
	return highlighted_content



def is_parenthesis(text):
	return text in map_parentheses



def is_operator(text, type):
	return text in map_operators[type]



def highlight_variable(v):
  return f'\\hlVar{{{v}}}'



def highlight_operator(o):
	return f'\\hlOprt{{{o}}}'



def highlight_constant(c):
	return f'\\hlConst{{{c}}}'



def highlight_function(f):
	return f'\\hlFunc{{{f}}}'



def highlight_literal(l):
  return f'\\hlLit{{{l}}}'



def highlight_comment(c):
  return f'\\hlCmt{{{c}}}'



def highlight_string(s):
  return f'\\hlStr{{{s}}}'



def highlight_text(t):
  return f'\\hlTxt{{{t}}}'



def highlight_level(text, level):
  levels = ['One', 'Two', 'Three', 'Four', 'Five', 'Six']
  return f'\\hlL{levels[level]}{{{text}}}'



# Implement tokenize_math, is_number, is_operator functions



process_latex_file("test.tex")