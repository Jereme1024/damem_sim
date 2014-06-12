/*
 * simics/magic-instruction.h
 *
 * This file is part of Virtutech Simics
 *
 * Copyright 1998-2009 Virtutech AB
 * 
 * This file is part of Virtutech Simics, which is distributed
 * under the Virtutech Simics Software License Agreement.
 *
 */

#ifndef _SIMICS_MAGIC_INSTRUCTION_H
#define _SIMICS_MAGIC_INSTRUCTION_H

/*
 * This file contains the magic instructions for different target
 * architectures, as understood by different compilers.
 *
 *   arch   instr           limit               compilers       additional requirements
 *   ----------------------------------------------------------------------------------
 *   h8300  brn n           -128 <= n <= 127    gcc
 *   ia64   nop 0x1?????    0 <= n < 0x100000   gcc
 *   mips   li $zero,n      0 <= n <= 0xffff    gcc
 *   msp430 bis r0,r0       n == 0              gcc
 *   ppc    rlwimi x,x,0,y,z (x<<10|y<<5|z) <= 0xffff  gcc
 *   ppc    mr n,n          0 <= n < 32         gcc             compat magic
 *   ppc64  fmr n,n         0 <= n < 32         gcc             compat magic
 *   sh     mov rn,rn       0 <= rn < 16        gcc
 *   sparc  sethi n,%g0     0 <  n < (1 << 22)  gcc, WS C[++]
 *   x86    cpuid           0 <= n < 0x100000   gcc             (eax & 0xffff0000) == 0x4711
 * 
 */

/*
  <add id="magic instruction figure">
  <figure label="magic_instruction_figure">
  <center>
  <table border="cross">
    <tr>
       <td><b>Target</b></td><td><b>Magic instruction</b></td>
                        <td><b>Conditions on <arg>n</arg></b></td>
    </tr>
    <tr>  
       <td>Alpha</td><td><i>binary:</i> <tt>0x70000000</tt></td>
                     <td><i><math>n = 0</math></i></td>
    </tr>
    <tr>
       <td>ARM</td><td><tt>orreq rn, rn, rn</tt></td>
                   <td><math>0 &lt;= n &lt; 15</math></td>
    </tr>
    <tr>
       <td>H8300</td><td><tt>brn n</tt></td>
                     <td><math>-128 &lt;= n &lt;= 127</math></td>
    </tr>
    <tr>
       <td>IA-64</td><td><tt>nop (0x100000 + n)</tt></td>
                    <td><math>0 &lt;= n &lt; 0x100000</math></td>
    </tr>
    <tr>
       <td>MIPS</td><td><tt>li %zero, n</tt></td>
                    <td><math>0 &lt;= n &lt; 0x10000</math></td>
    </tr>
    <tr>
       <td>MSP430</td><td><tt>bis r0,r0</tt></td>
                      <td><math>n = 0</math></td>
    </tr>
    <tr>
       <td>PowerPC</td><td><tt>rlwimi x,x,0,y,z</tt></td>
       <td><math>0 &lt;= n &lt; 32768,
                 n = x &lt;&lt; 10 | y &lt;&lt; 5 | z</math></td>
    </tr>
    <tr>
       <td>SH</td><td><tt>mov rn, rn</tt></td>
                        <td><math>0 &lt;= n &lt; 16</math></td>
    </tr>
    <tr>
       <td>SPARC</td><td><tt>sethi n, %g0</tt></td>
               <td><math>1 &lt;= n &lt; 0x400000</math></td>
    </tr>
    <tr>
       <td>x86</td><td><tt>cpuid %bx, %bx</tt></td>
                   <td><math>0 &lt;= n &lt; 0x100000</math></td>
    </tr>
    <tr>
       <td>Cell SPU</td><td><tt>or n, n, n</tt></td>
                        <td><math>0 &lt;= n &lt; 128</math></td>
    </tr>
  </table>
  </center>
  <caption>Magic instructions for different Simics Targets</caption>
  </figure>
  </add>
*/

/* BEGIN EXPORT simics/magic-instruction.h */


#define MAGIC(n) /* do nothing */

#endif /* _SIMICS_MAGIC_INSTRUCTION_H */
