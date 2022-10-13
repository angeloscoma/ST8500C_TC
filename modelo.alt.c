
// Rotinas modificadas:
// 			a)posições no buffer


/*************************************/
read_pars()
{
   TxBuf[1]=ala_fp_ind;
   TxBuf[2]=ala_fp_cap;
   TxBuf[3]=ala_ten_a;
   TxBuf[4]=ala_ten_b;
   TxBuf[5]=ala_sc;
   TxBuf[6]=ala_subc;
   TxBuf[7]=ala_chtt;
   TxBuf[8]=ala_chtc;
   TxBuf[9]=make8(valor_tc, 0);
   TxBuf[10]=make8(valor_tc, 1);
   TxBuf[11]=make8(valor_tp, 0);
   TxBuf[12]=make8(valor_tp, 1);
   Txlen=13;
}


/*************************************/
write_pars()
{
   ala_fp_ind=RxBuf[1];
   ala_fp_cap=RxBuf[2];
   ala_ten_a=RxBuf[3];
   ala_ten_b=RxBuf[4];
   ala_sc=RxBuf[5];
   ala_subc=RxBuf[6];
   ala_chtt=RxBuf[7];
   ala_chtc=RxBuf[8];
   valor_tc = make16(RxBuf[10],RxBuf[9]);
   valor_tp = make16(RxBuf[12],RxBuf[11]);
   salva_programa();
 
}
