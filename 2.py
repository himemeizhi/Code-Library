f = open('main_h.tex','w')
f.write("""\documentclass[a4paper,5pt,twocolumn,titlepage]{article}

\usepackage{CJK}
\usepackage{ifthen}         % logic options
\usepackage{color}          % color image and color definition
\usepackage{calc}           % do size calculations
\usepackage{listings}       % format source code
\usepackage{fancyhdr}
\lstset{language=C++,showspaces=false,showstringspaces=true,%
tabsize=2,extendedchars=false,columns=fullflexible,%
escapeinside={/*@}{@*/}}
\usepackage{times}
\usepackage{lastpage}
\usepackage[a4paper, body={15true cm,25.5true cm},%
            headheight=4true cm]{geometry}
\usepackage[CJKbookmarks,bookmarks=true,linkcolor=black,citecolor=black,%
            pagecolor=black,colorlinks=true]{hyperref}
    
\usepackage{mathpazo}

\usepackage{pstricks,pst-node,pst-tree}

\usepackage{graphicx}
\usepackage{amsmath}
\usepackage{xcolor}
\usepackage{type1cm}
\usepackage{booktabs}
\usepackage{geometry}
%\usepackage[landscape]{geometry}
\geometry{left=2cm,right=1cm,top=1.5cm,bottom=2cm,headsep=0.2cm}

\usepackage{courier}
%\usepackage{time}
%\usepackage{charter}

\usepackage{fancyhdr}

%\usepackage{listings}
\AtBeginDvi{\special{pdf:tounicode UTF8-UCS2}}

\usepackage{indentfirst}

% style: list typesetting
\definecolor{grey}{rgb}{0.3,0.3,0.3}
\definecolor{darkgreen}{rgb}{0,0.3,0}
\definecolor{darkblue}{rgb}{0,0,0.3}
\lstset{%
% indexing
    numbers=left,
    numberstyle=\\tiny,%
% character display
    showstringspaces=false,
    showspaces=false,%
    tabsize=2,%
% style
    frame=lines,%
    basicstyle=\\tiny\\ttfamily,%
    keywordstyle=\color{darkblue}\\bfseries,%
    identifierstyle=,%
    commentstyle=\color{darkgreen},%\itshape,%
    stringstyle=\color{grey}%
} \lstloadlanguages{C,C++,Java}

\lstset{breaklines} \columnsep 1 cm \pagestyle{fancy}
\\fancyhead[L]{Perfect Freeze}
\\fancyhead[R]{\\thepage} \\fancyfoot{}
\\title{Code Library}
\\author{Himemiya Nanao}
\\begin{document}
\\begin{CJK*}{UTF8}{Source Code Pro}
\maketitle \\tableofcontents
\\newpage
\pagenumbering{arabic}

""")

import os
for x,y,z in os.walk('.'):
	if x == '.':
		continue
	f.write('\section{'+x[2:]+'}\n')
	for files in z:
		if ((files == '.ds_store') or (files == '.DS_Store') or (files.endswith('~')) or files.endswith('.pdf')):
			continue
		ot=files
		if ot.endswith(""".cpp"""):
		    ot=ot.rstrip(""".cpp""")
		elif ot.endswith(""".cxx"""):
		    ot=ot.rstrip(""".cxx""")
		elif ot.endswith("""java"""):
		    ot="java"
		f.write('\subsection{'+ot+'}\n')
		fname = x+'/'+files
		fname = fname.lower()
		if files.count('.')!=0:
			if fname.endswith(""".java"""):
				lang = """Java"""
			else:
				lang = """C++"""
			f.write('\\lstinputlisting[language='+lang+']{\"'+fname+'\"}\n')
#			print files.count('.')
#			print files
		else:
			f.write('\\lstinputlisting{\"'+fname+'\"}\n')
f.write(
"""
\end{CJK*}
\end{document}
""")
f.close()
