use super::{Char, Move};

pub const MOVE_LEFT: Move = 0;
pub const MOVE_STAY: Move = 1;
pub const MOVE_RIGHT: Move = 2;

const INITIAL_TAPE_CAPACITY: usize = 256;

#[derive(Debug, Default, Copy, Clone, Hash, Eq, PartialEq, Ord, PartialOrd)]
pub struct TapeMove {
    pub previous_value: Char,
    pub move_right: bool,
    pub move_left: bool,
}

impl TapeMove {
    fn new(previous_value: Char, move_right: bool, move_left: bool) -> Self {
        TapeMove {
            previous_value,
            move_right,
            move_left,
        }
    }
}

/// Turing machine tape
#[derive(Debug, Clone)]
pub struct Tape {
    tape: Vec<Char>,
    position: usize,
    max_size: usize,
    ind_left: usize,
    ind_right: usize,
}

impl Tape {
    /// Creates a new blank tape.
    pub fn new() -> Self {
        let position = INITIAL_TAPE_CAPACITY / 2;
        Tape {
            tape: vec![0; INITIAL_TAPE_CAPACITY],
            position,
            max_size: INITIAL_TAPE_CAPACITY,
            ind_left: position - 1,
            ind_right: position + 1,
        }
    }

    /// Creates a new tape with the given data and head position.
    /// relative to the data slice.
    ///
    /// # Panic
    ///
    /// Panics if `position` is not in the range `0..position.len()`.
    pub fn from_slice(data: &[Char], position: usize) -> Self {
        assert!(position <= data.len());
        // build a vector with zeros on the edges
        let mut tape = Vec::with_capacity(data.len() + 2);
        tape.push(0);
        tape.extend_from_slice(data);
        tape.push(0);
        let max_size = tape.len();

        Tape {
            tape,
            position: position + 1,
            max_size: max_size,
            ind_left: 0,
            ind_right: max_size - 1,
        }
    }

    /// Reads the symbol at the tape's head.
    pub fn read(&self) -> Char {
        self.tape[self.position]
    }

    /// Reset the tape into a blank tape. The memory allocated internally is
    /// retained.
    pub fn reset(&mut self) {
        for c in &mut self.tape {
            *c = 0;
        }
        self.ind_left = self.position - 1;
        self.ind_right = self.position + 1;
    }

    pub fn write_and_move(&mut self, relative_pos: Move, value: Char) -> TapeMove {
        eprintln!("write_and_move({}, {})", relative_pos, value);
        let mut tape_move = TapeMove::new(0, false, false);
        self.tape[self.position] = value;

        let replace_pos = dbg!(relative_pos as isize - 1);
        self.position = dbg!(((self.position as isize) + replace_pos) as usize);

        if self.position >= self.max_size {
            self.reserve_right(self.max_size);
        } else if self.position == 0 {
            self.reserve_left(self.max_size);
        }

        if self.position >= self.ind_right {
            self.ind_right = self.position + 1;
            tape_move.move_right = true;
        } else if self.position <= self.ind_left {
            self.ind_left = self.position - 1;
            tape_move.move_left = true;
        }

        tape_move
    }

    fn reserve_left(&mut self, amt: usize) {
        eprintln!("reserve_left({})", amt);
        self.max_size += amt;
        let tape2 = self.tape.clone();
        for c in &mut self.tape {
            *c = 0;
        }
        self.tape.resize(amt, 0);
        self.tape.extend_from_slice(&tape2);
        self.position += amt;
        self.ind_right += amt;
        self.ind_left += amt;
    }

    fn reserve_right(&mut self, amt: usize) {
        self.max_size += amt;
        self.tape.resize(self.max_size, 0);
    }

    fn first_non_blank(&self) -> Option<usize> {
        self.tape[self.ind_left + 1..]
            .iter()
            .position(|v| *v != 0)
            .map(|p| self.ind_left + 1 + p)
    }

    fn last_non_blank(&self) -> Option<usize> {
        self.tape[..self.ind_right]
            .iter()
            .rev()
            .position(|v| *v != 0)
            .map(|p| self.ind_right - 1 - p)
    }

    /// Obtains a slice of the tape with non-zero content.
    pub fn non_blank(&self) -> &[Char] {
        if let Some(left) = self.first_non_blank() {
            if let Some(right) = self.last_non_blank() {
                return &self.tape[left..=right];
            }
        }
        &[]
    }

    /// Obtains a slice of the tape with non-zero content,
    /// plus the position of the head relative to that slice.
    ///
    /// Since the head could be pointing at a position before
    /// the non-zero content, this position can be negative.
    pub fn non_blank_and_head(&self) -> Option<(&[Char], isize)> {
        if let Some(left) = self.first_non_blank() {
            if let Some(right) = self.last_non_blank() {
                return Some((
                    &self.tape[left..=right],
                    self.position as isize - left as isize,
                ));
            }
        }
        None
    }
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn smoke_test() {
        let mut tape = Tape::new();
        assert_eq!(tape.non_blank_and_head(), None);

        tape.write_and_move(1, MOVE_STAY);
        assert_eq!(tape.non_blank_and_head(), Some((&[1][..], 0)));

        tape.write_and_move(9, MOVE_LEFT);
        assert_eq!(tape.non_blank_and_head(), Some((&[9][..], -1)));
    }

    #[test]
    fn test_non_blank() {
        let tape = Tape::from_slice(&[0, 1, 2, 3, 4, 5, 0, 0], 5);
        assert_eq!(tape.non_blank(), &[1, 2, 3, 4, 5]);
        assert_eq!(tape.non_blank_and_head(), Some((&[1, 2, 3, 4, 5][..], 4)));

        let tape = Tape::from_slice(&[1, 0, 1, 0, 1, 0, 1], 0);
        assert_eq!(tape.non_blank(), &[1, 0, 1, 0, 1, 0, 1]);

        let tape = Tape::from_slice(&[0, 0, 0, 0, 0, 0, 0], 4);
        assert_eq!(tape.non_blank(), &[]);
    }


    #[test]
    fn test_write_and_move() {
        let mut tape = Tape::from_slice(&[0, 1, 2, 3, 4, 5, 0, 0], 0);
        assert_eq!(tape.non_blank_and_head(), Some((&[1, 2, 3, 4, 5][..], -1)));

        tape.write_and_move(1, MOVE_LEFT);
        assert_eq!(tape.non_blank_and_head(), Some((&[1, 1, 2, 3, 4, 5][..], -1)));

        tape.write_and_move(6, MOVE_STAY);
        assert_eq!(tape.non_blank_and_head(), Some((&[6, 1, 1, 2, 3, 4, 5][..], 0)));

        tape.write_and_move(0, MOVE_RIGHT);
        assert_eq!(tape.non_blank_and_head(), Some((&[1, 1, 2, 3, 4, 5][..], 0)));

        tape.write_and_move(3, MOVE_RIGHT);
        assert_eq!(tape.non_blank_and_head(), Some((&[3, 1, 2, 3, 4, 5][..], 1)));

        tape.write_and_move(2, MOVE_STAY);
        assert_eq!(tape.non_blank_and_head(), Some((&[3, 2, 2, 3, 4, 5][..], 1)));
    }
}
