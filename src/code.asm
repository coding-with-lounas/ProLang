TITLE code.asm
PILE SEGMENT STACK
    DW 100 DUP(?)
base_pile EQU $
PILE ENDS

DATA SEGMENT
    a DW ?
    b DW ?
    Max DW ?
    i DW ?
    j DW ?
    k DW ?
    x DW ?
    y DW ?
    z DW ?
    Tabint DW 50 DUP(?)
    Tabfloat DW 30 DUP(?)
    somme DW ?
    moyenne DW ?
    Pi DW ?
    t1 DW ?
    t2 DW ?
    t3 DW ?
    t4 DW ?
    t5 DW ?
    t6 DW ?
    t7 DW ?
    t8 DW ?
    t9 DW ?
    t10 DW ?
    t11 DW ?
    t12 DW ?
    t13 DW ?
    t15 DW ?
    t16 DW ?
    t17 DW ?
    t18 DW ?
    t19 DW ?
    t20 DW ?
    t21 DW ?
    t22 DW ?
    t24 DW ?
    t25 DW ?
    t26 DW ?
    t27 DW ?
    t28 DW ?
    t29 DW ?
    t30 DW ?
    t31 DW ?
    t32 DW ?
    t33 DW ?
    t34 DW ?
    t35 DW ?
    t36 DW ?
    t37 DW ?
    t38 DW ?
    t39 DW ?
    t40 DW ?
    t41 DW ?
    t42 DW ?
    t43 DW ?
    t44 DW ?
    t45 DW ?
    t46 DW ?
    t47 DW ?
    t48 DW ?
    t49 DW ?
    t50 DW ?
    t51 DW ?
    t52 DW ?
    msg0 DB "Valeur finale de x: ", '$'
    msg1 DB "Somme: ", '$'
    msg2 DB "Moyenne: ", '$'
    newline DB 10, 13, '$'
DATA ENDS

CODE SEGMENT
MAIN:
    ASSUME CS:CODE, DS:DATA, SS:PILE
    MOV AX, DATA
    MOV DS, AX
    MOV AX, PILE
    MOV SS, AX
    MOV SP, base_pile

QUAD_0:
    MOV AX, 10
    MOV x, AX
QUAD_1:
    MOV AX, 5
    MOV y, AX
QUAD_2:
    MOV AX, 2
    MOV z, AX
QUAD_3:
    MOV AX, 2
    MOV a, AX
QUAD_4:
    MOV AX, 2
    ADD AX, Pi
    MOV t1, AX
QUAD_5:
    MOV AX, t1
    MOV BX, 2
    IMUL BX
    MOV t2, AX
QUAD_6:
    MOV AX, t2
    MOV b, AX
QUAD_7:
    MOV AX, 5
    MOV BX, 2
    IMUL BX
    MOV t3, AX
QUAD_8:
    MOV AX, 10
    ADD AX, t3
    MOV t4, AX
QUAD_9:
    MOV AX, t4
    MOV DI, 0
    ADD DI, DI
    MOV Tabint[DI], AX
QUAD_10:
    MOV AX, t2
    ADD AX, 3
    MOV t5, AX
QUAD_11:
    MOV AX, t5
    CWD
    MOV BX, 2
    IDIV BX
    MOV t6, AX
QUAD_12:
    MOV AX, t6
    MOV DI, 1
    ADD DI, DI
    MOV Tabfloat[DI], AX
QUAD_13:
    MOV AX, 10
    CMP AX, 5
    MOV AX, 1
    JG TRUE_0
    MOV AX, 0
TRUE_0:
    MOV t7, AX
QUAD_14:
    MOV AX, 10
    ADD AX, 5
    MOV t8, AX
QUAD_15:
    MOV AX, 2
    CMP AX, t8
    MOV AX, 1
    JL TRUE_1
    MOV AX, 0
TRUE_1:
    MOV t9, AX
QUAD_16:
    MOV AX, t7
    AND AX, t9
    MOV t10, AX
QUAD_17:
    MOV AX, 5
    CMP AX, 0
    MOV AX, 1
    JE TRUE_2
    MOV AX, 0
TRUE_2:
    MOV t11, AX
QUAD_18:
    MOV AX, t11
    CMP AX, 0
    JE IS_ZERO_3
    MOV AX, 0
    JMP DONE_NOT_3
IS_ZERO_3:
    MOV AX, 1
DONE_NOT_3:
    MOV t12, AX
QUAD_19:
    MOV AX, t10
    OR AX, t12
    MOV t13, AX
QUAD_20:
    MOV AX, t13
    CMP AX, 0
    JE QUAD_46
QUAD_22:
    MOV AX, t8
    ADD AX, 2
    MOV t15, AX
QUAD_23:
    MOV AX, t15
    MOV somme, AX
QUAD_24:
    MOV AX, 0
    MOV i, AX
QUAD_25:
    MOV AX, i
    CMP AX, 10
    MOV AX, 1
    JLE TRUE_4
    MOV AX, 0
TRUE_4:
    MOV t16, AX
QUAD_26:
    MOV AX, t16
    CMP AX, 0
    JE QUAD_45
QUAD_27:
    MOV SI, i
    ADD SI, SI
    MOV AX, Tabint[SI]
    MOV t17, AX
QUAD_28:
    MOV AX, t17
    ADD AX, i
    MOV t18, AX
QUAD_29:
    MOV AX, t18
    MOV DI, i
    ADD DI, DI
    MOV Tabint[DI], AX
QUAD_30:
    MOV AX, i
    CMP AX, 5
    MOV AX, 1
    JL TRUE_5
    MOV AX, 0
TRUE_5:
    MOV t19, AX
QUAD_31:
    MOV SI, i
    ADD SI, SI
    MOV AX, Tabint[SI]
    MOV t20, AX
QUAD_32:
    MOV AX, t20
    CMP AX, 10
    MOV AX, 1
    JG TRUE_6
    MOV AX, 0
TRUE_6:
    MOV t21, AX
QUAD_33:
    MOV AX, t19
    AND AX, t21
    MOV t22, AX
QUAD_34:
    MOV AX, t22
    CMP AX, 0
    JE QUAD_39
QUAD_36:
    MOV AX, t20
    MOV BX, 1
    IMUL BX
    MOV t24, AX
QUAD_37:
    MOV AX, t24
    MOV DI, i
    ADD DI, DI
    MOV Tabfloat[DI], AX
QUAD_38:
    JMP QUAD_42
QUAD_39:
    MOV SI, i
    ADD SI, SI
    MOV AX, Tabint[SI]
    MOV t25, AX
QUAD_40:
    MOV AX, t25
    CWD
    MOV BX, 2
    IDIV BX
    MOV t26, AX
QUAD_41:
    MOV AX, t26
    MOV DI, i
    ADD DI, DI
    MOV Tabfloat[DI], AX
QUAD_42:
    MOV AX, i
    ADD AX, 1
    MOV t27, AX
QUAD_43:
    MOV AX, t27
    MOV i, AX
QUAD_44:
    JMP QUAD_25
QUAD_45:
    JMP QUAD_47
QUAD_46:
    MOV AX, 0
    MOV somme, AX
QUAD_47:
    MOV AX, x
    CMP AX, Max
    MOV AX, 1
    JLE TRUE_7
    MOV AX, 0
TRUE_7:
    MOV t28, AX
QUAD_48:
    MOV AX, y
    CMP AX, 0
    MOV AX, 1
    JNE TRUE_8
    MOV AX, 0
TRUE_8:
    MOV t29, AX
QUAD_49:
    MOV AX, z
    CMP AX, 10
    MOV AX, 1
    JL TRUE_9
    MOV AX, 0
TRUE_9:
    MOV t30, AX
QUAD_50:
    MOV AX, t29
    OR AX, t30
    MOV t31, AX
QUAD_51:
    MOV AX, t28
    AND AX, t31
    MOV t32, AX
QUAD_52:
    MOV AX, t32
    CMP AX, 0
    JE QUAD_69
QUAD_53:
    MOV AX, x
    ADD AX, 1
    MOV t33, AX
QUAD_54:
    MOV AX, t33
    MOV x, AX
QUAD_55:
    MOV AX, x
    CMP AX, y
    MOV AX, 1
    JE TRUE_10
    MOV AX, 0
TRUE_10:
    MOV t34, AX
QUAD_56:
    MOV AX, t34
    CMP AX, 0
    JE IS_ZERO_11
    MOV AX, 0
    JMP DONE_NOT_11
IS_ZERO_11:
    MOV AX, 1
DONE_NOT_11:
    MOV t35, AX
QUAD_57:
    MOV AX, t35
    CMP AX, 0
    JE QUAD_68
QUAD_58:
    MOV AX, y
    ADD AX, 1
    MOV t36, AX
QUAD_59:
    MOV AX, t36
    MOV y, AX
QUAD_60:
    MOV AX, x
    ADD AX, 1
    MOV t37, AX
QUAD_61:
    MOV SI, 0
    ADD SI, SI
    MOV AX, Tabint[SI]
    MOV t38, AX
QUAD_62:
    MOV SI, 1
    ADD SI, SI
    MOV AX, Tabint[SI]
    MOV t39, AX
QUAD_63:
    MOV AX, t38
    ADD AX, t39
    MOV t40, AX
QUAD_64:
    MOV AX, x
    SUB AX, t36
    MOV t41, AX
QUAD_65:
    MOV AX, t40
    IMUL t41
    MOV t42, AX
QUAD_66:
    MOV AX, t42
    MOV DI, t37
    ADD DI, DI
    MOV Tabint[DI], AX
QUAD_67:
    JMP QUAD_55
QUAD_68:
    JMP QUAD_47
QUAD_69:
    MOV AX, 1
    MOV j, AX
QUAD_70:
    MOV AX, j
    CMP AX, 20
    MOV AX, 1
    JLE TRUE_12
    MOV AX, 0
TRUE_12:
    MOV t43, AX
QUAD_71:
    MOV AX, t43
    CMP AX, 0
    JE QUAD_84
QUAD_72:
    MOV AX, j
    SUB AX, 1
    MOV t44, AX
QUAD_73:
    MOV SI, t44
    ADD SI, SI
    MOV AX, Tabfloat[SI]
    MOV t45, AX
QUAD_74:
    MOV SI, j
    ADD SI, SI
    MOV AX, Tabfloat[SI]
    MOV t46, AX
QUAD_75:
    MOV AX, t45
    ADD AX, t46
    MOV t47, AX
QUAD_76:
    MOV AX, t47
    CWD
    MOV BX, 2
    IDIV BX
    MOV t48, AX
QUAD_77:
    MOV AX, t48
    MOV DI, j
    ADD DI, DI
    MOV Tabfloat[DI], AX
QUAD_78:
    MOV SI, j
    ADD SI, SI
    MOV AX, Tabfloat[SI]
    MOV t49, AX
QUAD_79:
    MOV AX, moyenne
    ADD AX, t49
    MOV t50, AX
QUAD_80:
    MOV AX, t50
    MOV moyenne, AX
QUAD_81:
    MOV AX, j
    ADD AX, 1
    MOV t51, AX
QUAD_82:
    MOV AX, t51
    MOV j, AX
QUAD_83:
    JMP QUAD_70
QUAD_84:
    MOV AX, moyenne
    CWD
    MOV BX, 20
    IDIV BX
    MOV t52, AX
QUAD_85:
    MOV AX, t52
    MOV moyenne, AX
QUAD_86:
QUAD_87:
    MOV DX, OFFSET msg0
    MOV AH, 09h
    INT 21h
    ; TODO: Print value of x (omitted for brevity)
    MOV DX, OFFSET newline
    MOV AH, 09h
    INT 21h
QUAD_88:
    MOV DX, OFFSET msg1
    MOV AH, 09h
    INT 21h
    ; TODO: Print value of somme (omitted for brevity)
    MOV DX, OFFSET newline
    MOV AH, 09h
    INT 21h
QUAD_89:
    MOV DX, OFFSET msg2
    MOV AH, 09h
    INT 21h
    ; TODO: Print value of moyenne (omitted for brevity)
    MOV DX, OFFSET newline
    MOV AH, 09h
    INT 21h
QUAD_90:
    MOV AH, 4Ch
    INT 21h
CODE ENDS
END MAIN
