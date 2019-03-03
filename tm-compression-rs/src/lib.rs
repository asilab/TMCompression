type TmId = u64;
type RecordId = u64;
type Char = u32;
type Move = u32;
type State = u32;

#[derive(Debug, Default, Copy, Clone, Eq, PartialEq, Ord, PartialOrd)]
pub struct TuringRecord {
    write: Char,
    mov: Move,
    state: State,
}

impl TuringRecord {
    pub fn from_id(id: RecordId, number_of_states: u32, alphabet_size: u32) -> Self {
        // order of significance (least to most): character_write -> tape_move -> state
        let nstates = number_of_states as RecordId;
        let nalphabet = alphabet_size as RecordId;
        let mut rest = id;
        let write = (rest % nalphabet) as Char;
        rest /= nalphabet;
        let mov = (rest % 3) as Move;
        rest /= 3;
        let state = (rest % nstates) as State;
        TuringRecord { write, mov, state }
    }

    pub fn calculate_id(&self) -> RecordId {
        unimplemented!("not needed")
    }

    pub fn next(&mut self, number_of_states: u32, alphabet_size: u32) -> bool {
        if self.write < alphabet_size - 1 {
            self.write += 1;
            return true;
        }
        self.write = 0;
        if self.mov < 2 {
            self.mov += 1;
            return true;
        }

        self.mov = 0;
        if self.state < number_of_states - 1 {
            self.state += 1;
            return true;
        }

        self.state = 0;
        false
    }
}

#[derive(Debug, Clone, Eq, PartialEq, Ord, PartialOrd)]
pub struct StateMatrix {
    v: Vec<TuringRecord>,
    nb_states: u32,
    alph_sz: u32,
}

impl StateMatrix {
    pub fn new(number_of_states: u32, alphabet_size: u32) -> Self {
        StateMatrix {
            v: vec![TuringRecord::default(); (number_of_states * alphabet_size) as usize],
            nb_states: number_of_states,
            alph_sz: alphabet_size,
        }
    }

    pub fn from_id(id: TmId, number_of_states: u32, alphabet_size: u32) -> Self {
        let mut o = StateMatrix::new(number_of_states, alphabet_size);
        o.set_by_id(id);
        o
    }

    pub fn set_by_id(&mut self, id: TmId) {
        let mut rest = id;
        let record_cardinality = (self.nb_states * self.alph_sz * 3) as u64;
        for st in &mut self.v {
            let state_id = rest % record_cardinality;
            *st = TuringRecord::from_id(state_id, self.nb_states, self.alph_sz);
            rest /= record_cardinality;
            if rest == 0 {
                break;
            }
        }
    }

    pub fn next(&mut self) -> bool {
        for e in &mut self.v {
            if e.next(self.nb_states, self.alph_sz) {
                return true;
            }
        }
        false
    }

    pub fn calculate_id(&self) -> TmId {
        //Problem when jobs>1 ;
        let record_cardinality = (self.nb_states * self.alph_sz * 3) as u64;
        let mut id = 0;
        for st in self.v.iter().rev() {
            let st_index = st.write + (st.mov + st.state * 3) * self.alph_sz;
            id = id * record_cardinality + u64::from(st_index);
        }
        id
    }
}

#[cfg(test)]
mod tests {
    use crate::*;
    #[test]
    fn test_turing_record() {
        assert_eq!(
            TuringRecord::from_id(0, 10, 10),
            TuringRecord {
                write: 0,
                mov: 0,
                state: 0,
            }
        )
    }

    #[test]
    fn test_state_matrix_2_2() {
        let mut sm = StateMatrix::new(2, 2);

        for id in 0..20736 {
            assert_eq!(sm.calculate_id(), id,);
            sm.next();
        }
    }

    #[test]
    fn test_state_matrix_2_3() {
        let mut sm = StateMatrix::new(2, 3);

        for id in 0..34012224 {
            assert_eq!(sm.calculate_id(), id);
            sm.next();
        }
    }
}
