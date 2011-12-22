(* 
 *
 * MATLAB Engine Interface to Mathematica 
 *
 * Version 0.61 
 *
 * Robert, zhangchenhui99@mails.tsinghua.edu.cn
 *
 * mEngine provides the facility to share data between Mathematica and MATLAB. 
 * All functions are wrappers to those provided by the MATLAB Engine Library.
 * MATLAB should be installed first.
 *
 *)

BeginPackage["mEngine`"]

mShow::usage=	
	"mShow[] shows the MATLAB command window."

mHide::usage=
	"mHide[] hides the MATLAB command window."

mCmd::usage=
	"mCmd[\"command\"] executes command in MATLAB, and returns the output string."

mCmd::arg=
	"The argument to mCmd should be a string."

mPut::usage=
	"mPut[\"x\"] puts variable x into the MATLAB workspace."

mPut::arg=
	"The argument to mPut should either be a string corresponding to a variable name, 
	or a list of such strings."

mGet::usage=
	"mGet[\"x\"] gets variable x from the MATLAB workspace."

mGet::arg=
	"The argument to mGet should either be a string corresponding to a variable name, 
	or a list of such strings."

(* This imports all the eng functions *)
(*eng = Install["mEngine.exe"] *)
(*eng = Install["mEngineSource/mEngine"] *)

Begin["`Private`"]

ToMLB[m_] := 
Switch[
	TensorRank[m],
	0, {{m}}, 
	1, Transpose[{m}], 
	2, Transpose[m],
	_, Map[Transpose, m, {TensorRank[m] - 2}]
]

mShow[___] := engVis[1]

mHide[___] := engVis[0]

mCmd[cmd_String]/;engIsOpen[] := engCmd[cmd]

mCmd[cmd_String]/;!engIsOpen[] := (engOpen[]; mCmd[cmd])

mCmd[___] := Message[mCmd::arg]


mPut[s_String]/;engIsOpen[] :=
Module[
	{x, xmlb, dimlab, re, im},
	x = Symbol[s];
	xmlb = ToMLB[x];
	dimlab = Reverse[Dimensions[xmlb]];
	If[
		MemberQ[x, _Complex, {TensorRank[x]}],
		engPut[
			s,
			dimlab,
			N[Re /@ Flatten[xmlb]],
			N[Im /@ Flatten[xmlb]]
		],
		engPut[
			s, 
			dimlab,
			N[Flatten[xmlb]]
		]
	]
]

mPut[s_String]/;!engIsOpen[] := (engOpen[]; mPut[s])

mPut[___]:= Message[mPut::arg]

Attributes[mPut]:= {Listable}


mGet[s_String]:=
Module[
	{x, ret},
	x = engGet[s];
	If[
		x === $Failed,
		$Failed,
		Switch[
			TensorRank[x],
			2, Transpose[x],
			_, Map[Transpose, x, {TensorRank[x] - 2}]
		]
	]
]

mGet[___] := Message[mGet::arg]

Attributes[mGet] := {Listable}

End[ ]

EndPackage[ ]
